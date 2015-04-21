#include "FileInfo.h"
#include "MByteBuffer.h"
#include "UnArchiveParam.h"
#include "ArchiveParam.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include "Config.h"
#include "MLzma.h"
#include "CharsetConv.h"
#include "PakPathSplitInfo.h"
#include "LogSys.h"
#include "ArchiveData.h"

#include <stdlib.h>
#include <sstream>

BEGIN_NAMESPACE_FILEARCHIVETOOL

FileHeader::FileHeader():
	m_fileOffset(0), m_fileSize(0)
{
	m_pFullPath = new char[MAX_PATH];
	memset(m_pFullPath, 0, MAX_PATH);
	m_fileNamePath = new char[MAX_PATH];
	memset(m_fileNamePath, 0, MAX_PATH);
}

FileHeader::~FileHeader()
{
	delete m_pFullPath;
	delete m_fileNamePath;
}

void FileHeader::setFullPath(const char* dir, const char* fileName)
{
	strcat(m_pFullPath, dir);
	strcat(m_pFullPath, "/");
	strcat(m_pFullPath, fileName);
}

char* FileHeader::getFullPath()
{
	return m_pFullPath;
}

void FileHeader::setFileName(const char* fileName)
{
	strcpy(m_fileNamePath, fileName);
}

char* FileHeader::getFileName()
{
	return m_fileNamePath;
}

void FileHeader::writeFile2ArchiveFile(FILE* fileHandle)
{
	FILE* localFile = fopen(m_pFullPath, "rb");

	char* pchar;
	std::stringstream ss;//创建一个流

	if (localFile != nullptr)
	{
		ss.clear();
		ss.str("");
		ss << "打包局部文件 [" << m_pFullPath << "] 打开成功\n";

		// 计算文件大小
		fseek(localFile, 0, SEEK_END); //定位到文件末
		m_fileSize = ftell(localFile); //文件长度

		fseek(localFile, 0, SEEK_SET);	// 移动到文件头

		// 一次性读取进来，可能需要压缩
		pchar = new char[m_fileSize + 1];
		memset(pchar, 0, m_fileSize + 1);

		size_t readlength = fread(pchar, 1, m_fileSize, localFile);
		size_t writeLength;
		if (readlength == m_fileSize)
		{
			ss.clear();
			ss.str("");
			ss << "局部文件 [" << m_pFullPath << "] 读取成功\n";

			if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())
			{
				writeLength = fwrite(pchar, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{
					ss.clear();
					ss.str("");
					ss << "局部文件 [" << m_pFullPath << "] 非压缩写入打包文件失败\n";
				}
			}
			else	// 需要压缩
			{
				char* pComprStr = nullptr;		// 压缩的字符串指针
				MLzma::LzmaStrCompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{
					ss.clear();
					ss.str("");
					ss << "局部文件 [" << m_pFullPath << "] 压缩写入打包文件失败\n";
				}

				free(pComprStr);		// 记得释放这个内存
			}
		}
		else			// 读取可能有问题，读取不了完整文件
		{
			ss.clear();
			ss.str("");
			ss << "局部文件 [" << m_pFullPath << "] 读取失败\n";
		}

		delete []pchar;

		fclose(localFile);
	}
	else
	{
		ss.clear();
		ss.str("");
		ss << "打包局部文件 [" << m_pFullPath << "] 打开失败\n";
	}
}

uint32 FileHeader::calcHeaderSize()
{
	return sizeof(m_pathLen) + m_pathLen + sizeof(m_fileSize) + sizeof(m_fileOffset);
}

void FileHeader::writeHeader2ArchiveFile(FILE* fileHandle)
{
	fwrite(&m_pathLen, sizeof(m_pathLen), 1, fileHandle);
	// 写入 Utf8 编码的字符串
	//fwrite(m_fileNamePath, strlen(m_fileNamePath), 1, fileHandle);
	char* pUtf8Path = (FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8Str(m_fileNamePath));
	fwrite(pUtf8Path, m_pathLen, 1, fileHandle);
	fwrite(&m_fileOffset, sizeof(m_fileOffset), 1, fileHandle);
	fwrite(&m_fileSize, sizeof(m_fileSize), 1, fileHandle);
}

void FileHeader::readHeaderFromArchiveFile(MByteBuffer* ba)
{
	ba->readUnsignedInt8(m_pathLen);
	memset(m_fileNamePath, 0, MAX_PATH);
	// 转换成 Local 编码字符串
	ba->readMultiByte(m_fileNamePath, m_pathLen);
	char* pUtf8Path = (FileArchiveToolSysDef->getCharsetConvPtr()->Utf8ToLocalStr(m_fileNamePath));
	memcpy(m_fileNamePath, pUtf8Path, m_pathLen);
	ba->readUnsignedInt32(m_fileOffset);
	ba->readUnsignedInt32(m_fileSize);
}

void FileHeader::adjustHeaderOffset(uint32 offset)
{
	m_fileOffset = offset;
}

uint32 FileHeader::getFileSize()
{
	return m_fileSize;
}

void FileHeader::writeArchiveFile2File(FILE* fileHandle, UnArchiveParam* pUnArchiveParam)
{
	strcat(m_pFullPath, FileArchiveToolSysDef->getConfigPtr()->getUnpakOutputRootPath().c_str());
	strcat(m_pFullPath, "/");
	strcat(m_pFullPath, m_fileNamePath);

	std::string strPath = FileArchiveToolSysDef->getUtilPtr()->getFullPathNoFileName(m_pFullPath);
	FileArchiveToolSysDef->getUtilPtr()->mkDir(strPath.c_str());		// 创建目录

	fseek(fileHandle, m_fileOffset, SEEK_SET);	// 移动到文件开始位置

	FILE* localFile = fopen(m_pFullPath, "wb");
	char* pchar;
	std::stringstream ss;//创建一个流

	if (localFile != nullptr)
	{
		ss.clear();
		ss.str("");
		ss << "解包局部文件 [" << m_pFullPath << "] 打开成功\n";

		// 一次性读取进来，可能需要压缩
		pchar = new char[m_fileSize + 1];
		memset(pchar, 0, m_fileSize + 1);

		size_t readlength = fread(pchar, 1, m_fileSize, fileHandle);
		size_t writeLength;
		if (readlength == m_fileSize)
		{
			ss.clear();
			ss.str("");
			ss << "读取打包文件文件 [" << pUnArchiveParam->getUnArchiveFilePath() << "] 成功\n";

			FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

			if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())		// 如果不压缩
			{
				writeLength = fwrite(pchar, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{
					ss.clear();
					ss.str("");
					ss << "提取打包文件 [" << pUnArchiveParam->getUnArchiveFilePath() << "] 中的文件 [" << m_pFullPath << "] 非解压缩写入失败\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
				else
				{
					ss.clear();
					ss.str("");
					ss << "提取打包文件 [" << pUnArchiveParam->getUnArchiveFilePath() << "] 中的文件 [" << m_pFullPath << "] 非解压缩写入成功\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
			}
			else	// 需要解压
			{
				char* pComprStr = nullptr;		// 压缩的字符串指针
				MLzma::LzmaStrUncompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{
					ss.clear();
					ss.str("");
					ss << "提取打包文件 [" << pUnArchiveParam->getUnArchiveFilePath() << "] 中的文件 [" << m_pFullPath << "] 解压缩写入失败\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
				else
				{
					ss.clear();
					ss.str("");
					ss << "提取打包文件 [" << pUnArchiveParam->getUnArchiveFilePath() << "] 中的文件 [" << m_pFullPath << "] 解压缩写入成功\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}

				free(pComprStr);		// 记得释放这个内存
			}
		}
		else							// 读取可能有问题，读取不了完整文件
		{
			ss.clear();
			ss.str("");
			ss << "读取打包文件文件 [" << pUnArchiveParam->getUnArchiveFilePath() << "] 失败\n";
		}

		//fflush(localFile);
		fclose(localFile);
	}
	else
	{
		ss.clear();
		ss.str("");
		ss << "解包局部文件 [" << m_pFullPath << "] 打开失败\n";
	}
}

void FileHeader::modifyArchiveFileName(ArchiveParam* pArchiveParam)
{
	if (strlen(m_pFullPath) != strlen(pArchiveParam->getArchiveDir()) + strlen(m_fileNamePath) + 1)
	{
		strcpy(m_fileNamePath, m_pFullPath + strlen(pArchiveParam->getArchiveDir()) + 1);
	}

	// 计算目录长度， utf-8 编码目录长度
	// m_pathLen = strlen(m_fileNamePath);
	m_pathLen = (uint8)(FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8StrLen(m_fileNamePath));
}

void FileHeader::initFileHeader(PakPathSplitInfo* pPakPathSplitInfo)
{
	m_fileSize = pPakPathSplitInfo->getFileOrigSize();
	setFullPath(pPakPathSplitInfo->getOrigPath().c_str(), pPakPathSplitInfo->getOrigFileName().c_str());
	setFileName(pPakPathSplitInfo->getOrigFileName().c_str());
	modifyArchiveFileName(FileArchiveToolSysDef->getArchiveDataPtr()->getArchiveParamPtr());
}

END_NAMESPACE_FILEARCHIVETOOL
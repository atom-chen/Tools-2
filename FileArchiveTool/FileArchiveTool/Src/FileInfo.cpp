#include "FileInfo.h"
#include "MByteBuffer.h"
#include "UnArchiveParam.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include "Config.h"
#include "MLzma.h"
#include <stdlib.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

FileHeader::FileHeader()
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

void FileHeader::writeFile2ArchiveFile(FILE* fileHandle)
{
	FILE* localFile = fopen(m_pFullPath, "rb");

	char* pchar;

	if (localFile != nullptr)
	{
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
			if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())
			{
				writeLength = fwrite(pchar, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{

				}
			}
			else	// 需要压缩
			{
				char* pComprStr = nullptr;		// 压缩的字符串指针
				MLzma::LzmaStrCompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{

				}

				free(pComprStr);		// 记得释放这个内存
			}
		}
		else			// 读取可能有问题，读取不了完整文件
		{

		}

		delete []pchar;

		fclose(localFile);
	}
}

uint32 FileHeader::calcHeaderSize()
{
	return sizeof(m_pathLen) + m_pathLen + sizeof(m_fileSize) + sizeof(m_fileOffset);
}

void FileHeader::writeHeader2ArchiveFile(FILE* fileHandle)
{
	fwrite(&m_pathLen, sizeof(m_pathLen), 1, fileHandle);
	fwrite(m_fileNamePath, strlen(m_fileNamePath), 1, fileHandle);
	fwrite(&m_fileOffset, sizeof(m_fileOffset), 1, fileHandle);
	fwrite(&m_fileSize, sizeof(m_fileSize), 1, fileHandle);
}

void FileHeader::readHeaderFromArchiveFile(MByteBuffer* ba)
{
	ba->readUnsignedInt8(m_pathLen);
	memset(m_fileNamePath, 0, MAX_PATH);
	ba->readMultiByte(m_fileNamePath, m_pathLen);
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
	strcat(m_pFullPath, pUnArchiveParam->getUnArchiveOutDir());
	strcat(m_pFullPath, "/");
	strcat(m_pFullPath, m_fileNamePath);

	std::string strPath = FileArchiveToolSysDef->getUtilPtr()->getFullPathNoFileName(m_pFullPath);
	FileArchiveToolSysDef->getUtilPtr()->mkDir(strPath.c_str());		// 创建目录

	//fseek(fileHandle, 0, SEEK_SET);		// 移动文件指针到头部
	fseek(fileHandle, m_fileOffset, SEEK_SET);	// 移动到文件开始位置

	FILE* localFile = fopen(m_pFullPath, "wb");
	char* pchar;

	if (localFile != nullptr)
	{
		// 一次性读取进来，可能需要压缩
		pchar = new char[m_fileSize + 1];
		memset(pchar, 0, m_fileSize + 1);

		size_t readlength = fread(pchar, 1, m_fileSize, fileHandle);
		size_t writeLength;
		if (readlength == m_fileSize)
		{
			if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())		// 如果不压缩
			{
				writeLength = fwrite(pchar, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{

				}
			}
			else	// 需要解压
			{
				char* pComprStr = nullptr;		// 压缩的字符串指针
				MLzma::LzmaStrUncompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// 文件写入出现错误，不能写入完整文件
				{

				}

				free(pComprStr);		// 记得释放这个内存
			}
		}
		else							// 读取可能有问题，读取不了完整文件
		{

		}

		//fflush(localFile);
		fclose(localFile);
	}
}

END_NAMESPACE_FILEARCHIVETOOL
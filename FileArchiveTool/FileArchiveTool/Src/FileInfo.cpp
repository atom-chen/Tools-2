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
#include "PtrDefine.h"
#include "ArchiveCV.h"

#include <stdlib.h>
#include <sstream>

BEGIN_NAMESPACE_FILEARCHIVETOOL

FileHeader::FileHeader():
	m_fileOffset(0), m_fileSize(0), m_flags(0)
{
	m_pFullPath = new char[MAX_PATH];
	memset(m_pFullPath, 0, MAX_PATH);
	m_fileNamePath = new char[MAX_PATH];
	memset(m_fileNamePath, 0, MAX_PATH);
	m_pakFileNamePath = new char[MAX_PATH];
	memset(m_pakFileNamePath, 0, MAX_PATH);
}

FileHeader::~FileHeader()
{
	SAFE_DELETE(m_pFullPath);
	SAFE_DELETE(m_fileNamePath);
	SAFE_DELETE(m_pakFileNamePath);
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

char* FileHeader::getPakFileName()
{
	return m_pakFileNamePath;
}

void FileHeader::writeFile2ArchiveFile(FILE* fileHandle)
{
	FILE* localFile = fopen(m_pFullPath, "rb");

	char* pchar;
	std::stringstream ss;//����һ����

	if (localFile != nullptr)
	{
		ss.clear();
		ss.str("");
		ss << "����ֲ��ļ� [" << m_pFullPath << "] �򿪳ɹ�\n";

		FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

		// �����ļ���С
		fseek(localFile, 0, SEEK_END); //��λ���ļ�ĩ
		m_fileSize = ftell(localFile); //�ļ�����

		fseek(localFile, 0, SEEK_SET);	// �ƶ����ļ�ͷ

		// һ���Զ�ȡ������������Ҫѹ��
		pchar = new char[m_fileSize + 1];
		memset(pchar, 0, m_fileSize + 1);

		size_t readlength = fread(pchar, 1, m_fileSize, localFile);
		size_t writeLength;
		if (readlength == m_fileSize)
		{
			ss.clear();
			ss.str("");
			ss << "�ֲ��ļ� [" << m_pFullPath << "] ��ȡ�ɹ�\n";

			FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

			//if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())
			if (!FileArchiveToolSysDef->getUtilPtr()->checkFlags(eFHF_CPS, m_flags))
			{
				writeLength = fwrite(pchar, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// �ļ�д����ִ��󣬲���д�������ļ�
				{
					ss.clear();
					ss.str("");
					ss << "�ֲ��ļ� [" << m_pFullPath << "] ��ѹ��д�����ļ�ʧ��\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
				else
				{
					ss.clear();
					ss.str("");
					ss << "�ֲ��ļ� [" << m_pFullPath << "] ��ѹ��д�����ļ��ɹ�\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
			}
			else	// ��Ҫѹ��
			{
				char* pComprStr = nullptr;		// ѹ�����ַ���ָ��
				MLzma::LzmaStrCompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, fileHandle);
				if (writeLength != m_fileSize)		// �ļ�д����ִ��󣬲���д�������ļ�
				{
					ss.clear();
					ss.str("");
					ss << "�ֲ��ļ� [" << m_pFullPath << "] ѹ��д�����ļ�ʧ��\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
				else
				{
					ss.clear();
					ss.str("");
					ss << "�ֲ��ļ� [" << m_pFullPath << "] ��ѹ��д�����ļ��ɹ�\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}

				free(pComprStr);		// �ǵ��ͷ�����ڴ�
			}
		}
		else			// ��ȡ���������⣬��ȡ���������ļ�
		{
			ss.clear();
			ss.str("");
			ss << "�ֲ��ļ� [" << m_pFullPath << "] ��ȡʧ��\n";

			FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
		}

		SAFE_DELETE_ARRAY(pchar);

		fclose(localFile);
	}
	else
	{
		ss.clear();
		ss.str("");
		ss << "����ֲ��ļ� [" << m_pFullPath << "] ��ʧ��\n";

		FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
	}
}

uint32 FileHeader::calcHeaderSize()
{
	return sizeof(m_pathLen) + m_pathLen + sizeof(m_fileSize) + sizeof(m_fileOffset) + sizeof(m_flags);
}

void FileHeader::writeHeader2ArchiveFile(FILE* fileHandle)
{
	// д��·��
	fwrite(&m_pathLen, sizeof(m_pathLen), 1, fileHandle);
	// д�� Utf8 ������ַ���
	//fwrite(m_fileNamePath, strlen(m_fileNamePath), 1, fileHandle);
	char* pUtf8Path = FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8Str(m_pakFileNamePath);
	fwrite(pUtf8Path, m_pathLen, 1, fileHandle);
	// д���ļ�ƫ��
	fwrite(&m_fileOffset, sizeof(m_fileOffset), 1, fileHandle);
	// д���С
	fwrite(&m_fileSize, sizeof(m_fileSize), 1, fileHandle);
	// д���ʶ�ֶ�
	fwrite(&m_flags, sizeof(m_flags), 1, fileHandle);
}

void FileHeader::readHeaderFromArchiveFile(MByteBuffer* ba)
{
	// ��ȡ�ļ�·��
	ba->readUnsignedInt8(m_pathLen);
	memset(m_pakFileNamePath, 0, MAX_PATH);
	// ת���� Local �����ַ���
	ba->readMultiByte(m_pakFileNamePath, m_pathLen);
	char* pUtf8Path = (FileArchiveToolSysDef->getCharsetConvPtr()->Utf8ToLocalStr(m_pakFileNamePath));
	memcpy(m_pakFileNamePath, pUtf8Path, m_pathLen);
	// ��ȡ�ļ�ƫ��
	ba->readUnsignedInt32(m_fileOffset);
	// ��ȡ�ļ���С
	ba->readUnsignedInt32(m_fileSize);
	// ��ȡ�ļ���ʶ
	ba->readUnsignedInt32(m_flags);
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
	strcat(m_pFullPath, m_pakFileNamePath);

	std::string strPath = FileArchiveToolSysDef->getUtilPtr()->getFullPathNoFileName(m_pFullPath);
	FileArchiveToolSysDef->getUtilPtr()->mkDir(strPath.c_str());		// ����Ŀ¼

	fseek(fileHandle, m_fileOffset, SEEK_SET);	// �ƶ����ļ���ʼλ��

	FILE* localFile = fopen(m_pFullPath, "wb");
	char* pchar;
	std::stringstream ss;//����һ����

	if (localFile != nullptr)
	{
		ss.clear();
		ss.str("");
		ss << "����ֲ��ļ� [" << m_pFullPath << "] �򿪳ɹ�\n";

		FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

		// һ���Զ�ȡ������������Ҫѹ��
		pchar = new char[m_fileSize + 1];
		memset(pchar, 0, m_fileSize + 1);

		size_t readlength = fread(pchar, 1, m_fileSize, fileHandle);
		size_t writeLength;
		if (readlength == m_fileSize)
		{
			ss.clear();
			ss.str("");
			ss << "��ȡ����ļ��ļ� [" << pUnArchiveParam->getUnArchiveFilePath() << "] �ɹ�\n";

			FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

			//if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())		// �����ѹ��
			if (!FileArchiveToolSysDef->getUtilPtr()->checkFlags(eFHF_CPS, m_flags))
			{
				writeLength = fwrite(pchar, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// �ļ�д����ִ��󣬲���д�������ļ�
				{
					ss.clear();
					ss.str("");
					ss << "��ȡ����ļ� [" << pUnArchiveParam->getUnArchiveFilePath() << "] �е��ļ� [" << m_pFullPath << "] �ǽ�ѹ��д��ʧ��\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
				else
				{
					ss.clear();
					ss.str("");
					ss << "��ȡ����ļ� [" << pUnArchiveParam->getUnArchiveFilePath() << "] �е��ļ� [" << m_pFullPath << "] �ǽ�ѹ��д��ɹ�\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
			}
			else	// ��Ҫ��ѹ
			{
				char* pComprStr = nullptr;		// ѹ�����ַ���ָ��
				MLzma::LzmaStrUncompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, localFile);
				if (writeLength != m_fileSize)		// �ļ�д����ִ��󣬲���д�������ļ�
				{
					ss.clear();
					ss.str("");
					ss << "��ȡ����ļ� [" << pUnArchiveParam->getUnArchiveFilePath() << "] �е��ļ� [" << m_pFullPath << "] ��ѹ��д��ʧ��\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}
				else
				{
					ss.clear();
					ss.str("");
					ss << "��ȡ����ļ� [" << pUnArchiveParam->getUnArchiveFilePath() << "] �е��ļ� [" << m_pFullPath << "] ��ѹ��д��ɹ�\n";

					FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
				}

				free(pComprStr);		// �ǵ��ͷ�����ڴ�
			}
		}
		else							// ��ȡ���������⣬��ȡ���������ļ�
		{
			ss.clear();
			ss.str("");
			ss << "��ȡ����ļ��ļ� [" << pUnArchiveParam->getUnArchiveFilePath() << "] ʧ��\n";

			FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
		}

		//fflush(localFile);
		fclose(localFile);
	}
	else
	{
		ss.clear();
		ss.str("");
		ss << "����ֲ��ļ� [" << m_pFullPath << "] ��ʧ��\n";

		FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());
	}
}

// ������������ļ�
void FileHeader::modifyArchiveFileName(ArchiveParam* pArchiveParam)
{
	memcpy(m_pakFileNamePath, m_fileNamePath, strlen(m_fileNamePath));
	std::string tmpPath = FileArchiveToolSysDef->getConfigPtr()->getPakInRootPath() + "/" + m_pakFileNamePath;
	if (m_pFullPath != tmpPath)			// ��������ڸ�Ŀ¼�µ��ļ�
	{
		strcpy(m_pakFileNamePath, m_pFullPath + strlen(FileArchiveToolSysDef->getConfigPtr()->getPakInRootPath().c_str()) + 1);
	}

	// ����Ŀ¼���ȣ� utf-8 ����Ŀ¼����
	// m_pathLen = strlen(m_fileNamePath);
	m_pathLen = (uint8)(FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8StrLen(m_pakFileNamePath));
}

void FileHeader::initFileHeader(PakPathSplitInfo* pPakPathSplitInfo)
{
	m_fileSize = pPakPathSplitInfo->getFileOrigSize();
	if (m_fileSize > PAK_BYTES_SIZE)
	{
		FileArchiveToolSysDef->getUtilPtr()->setFlags(eFHF_CPS, m_flags);
	}
	setFullPath(pPakPathSplitInfo->getOrigPath().c_str(), pPakPathSplitInfo->getOrigFileName().c_str());
	setFileName(pPakPathSplitInfo->getOrigFileName().c_str());
	modifyArchiveFileName(FileArchiveToolSysDef->getArchiveDataPtr()->getArchiveParamPtr());
}

END_NAMESPACE_FILEARCHIVETOOL
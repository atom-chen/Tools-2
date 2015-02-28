#include "FileInfo.h"
#include "MByteBuffer.h"
#include "UnArchiveParam.h"
#include "ArchiveParam.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include "Config.h"
#include "MLzma.h"
#include "CharsetConv.h"
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

void FileHeader::setFullPath(const char* dir, const char* fileName)
{
	strcat(m_pFullPath, dir);
	strcat(m_pFullPath, "/");
	strcat(m_pFullPath, fileName);
}

void FileHeader::setFileName(const char* fileName)
{
	strcpy(m_fileNamePath, fileName);
}

void FileHeader::writeFile2ArchiveFile(FILE* fileHandle)
{
	FILE* localFile = fopen(m_pFullPath, "rb");

	char* pchar;

	if (localFile != nullptr)
	{
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
			if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())
			{
				writeLength = fwrite(pchar, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// �ļ�д����ִ��󣬲���д�������ļ�
				{

				}
			}
			else	// ��Ҫѹ��
			{
				char* pComprStr = nullptr;		// ѹ�����ַ���ָ��
				MLzma::LzmaStrCompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, fileHandle);
				if (writeLength != readlength)		// �ļ�д����ִ��󣬲���д�������ļ�
				{

				}

				free(pComprStr);		// �ǵ��ͷ�����ڴ�
			}
		}
		else			// ��ȡ���������⣬��ȡ���������ļ�
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
	// д�� Utf8 ������ַ���
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
	// ת���� Local �����ַ���
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
	strcat(m_pFullPath, pUnArchiveParam->getUnArchiveOutDir());
	strcat(m_pFullPath, "/");
	strcat(m_pFullPath, m_fileNamePath);

	std::string strPath = FileArchiveToolSysDef->getUtilPtr()->getFullPathNoFileName(m_pFullPath);
	FileArchiveToolSysDef->getUtilPtr()->mkDir(strPath.c_str());		// ����Ŀ¼

	fseek(fileHandle, m_fileOffset, SEEK_SET);	// �ƶ����ļ���ʼλ��

	FILE* localFile = fopen(m_pFullPath, "wb");
	char* pchar;

	if (localFile != nullptr)
	{
		// һ���Զ�ȡ������������Ҫѹ��
		pchar = new char[m_fileSize + 1];
		memset(pchar, 0, m_fileSize + 1);

		size_t readlength = fread(pchar, 1, m_fileSize, fileHandle);
		size_t writeLength;
		if (readlength == m_fileSize)
		{
			if (!FileArchiveToolSysDef->getConfigPtr()->bCompress())		// �����ѹ��
			{
				writeLength = fwrite(pchar, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// �ļ�д����ִ��󣬲���д�������ļ�
				{

				}
			}
			else	// ��Ҫ��ѹ
			{
				char* pComprStr = nullptr;		// ѹ�����ַ���ָ��
				MLzma::LzmaStrUncompress(pchar, m_fileSize, &pComprStr, &m_fileSize);

				writeLength = fwrite(pComprStr, 1, m_fileSize, localFile);
				if (writeLength != readlength)		// �ļ�д����ִ��󣬲���д�������ļ�
				{

				}

				free(pComprStr);		// �ǵ��ͷ�����ڴ�
			}
		}
		else							// ��ȡ���������⣬��ȡ���������ļ�
		{

		}

		//fflush(localFile);
		fclose(localFile);
	}
}

void FileHeader::modifyArchiveFileName(ArchiveParam* pArchiveParam)
{
	if (strlen(m_pFullPath) != strlen(pArchiveParam->getArchiveDir()) + strlen(m_fileNamePath) + 1)
	{
		strcpy(m_fileNamePath, m_pFullPath + strlen(pArchiveParam->getArchiveDir()) + 1);
	}

	// ����Ŀ¼���ȣ� utf-8 ����Ŀ¼����
	// m_pathLen = strlen(m_fileNamePath);
	m_pathLen = (uint8)(FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8StrLen(m_fileNamePath));
}

END_NAMESPACE_FILEARCHIVETOOL
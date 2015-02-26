#include "FileInfo.h"
#include "MByteBuffer.h"
#include "UnArchiveParam.h"
#include "FileArchiveToolSys.h"
#include "Util.h"

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

void FileHeader::writeFile2ArchiveFile(FILE* fileHandle, uint32 sizePerOne, char* pchar)
{
	FILE* localFile = fopen(m_pFullPath, "rb");
	uint32 leftSize = m_fileSize;
	if (localFile != nullptr)
	{
		while (leftSize > 0)
		{
			if (leftSize > sizePerOne)
			{
				fread(pchar, sizePerOne, 1, localFile);
				fwrite(pchar, sizePerOne, 1, fileHandle);
				leftSize -= sizePerOne;
			}
			else
			{
				fread(pchar, leftSize, 1, localFile);
				fwrite(pchar, leftSize, 1, fileHandle);
				leftSize = 0;
			}
		}

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
	m_fileOffset += offset;
}

void FileHeader::writeArchiveFile2File(FILE* fileHandle, uint32 sizePerOne, char* pchar, UnArchiveParam* pUnArchiveParam)
{
	strcat(m_pFullPath, pUnArchiveParam->getUnArchiveOutDir());
	strcat(m_pFullPath, "/");
	strcat(m_pFullPath, m_fileNamePath);

	std::string strPath = FileArchiveToolSysDef->getUtilPtr()->getFullPathNoFileName(m_pFullPath);
	FileArchiveToolSysDef->getUtilPtr()->mkDir(strPath.c_str());		// 创建目录

	fseek(fileHandle, 0, SEEK_SET);		// 移动文件指针到头部
	fseek(fileHandle, m_fileOffset, SEEK_SET);	// 移动到文件开始位置

	FILE* localFile = fopen(m_pFullPath, "wb");
	uint32 leftSize = m_fileSize;
	if (localFile != nullptr)
	{
		while (leftSize > 0)
		{
			if (leftSize > sizePerOne)
			{
				fread(pchar, sizePerOne, 1, fileHandle);
				fwrite(pchar, sizePerOne, 1, localFile);
				leftSize -= sizePerOne;
			}
			else
			{
				fread(pchar, leftSize, 1, fileHandle);
				fwrite(pchar, leftSize, 1, localFile);
				leftSize = 0;
			}
		}

		fflush(localFile);
		fclose(localFile);
	}
}

END_NAMESPACE_FILEARCHIVETOOL
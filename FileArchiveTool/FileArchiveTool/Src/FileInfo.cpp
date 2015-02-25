#include "FileInfo.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

FileHeader::FileHeader()
{
	m_fileNamePath = new std::string();
}

FileHeader::~FileHeader()
{
	delete m_fileNamePath;
}

void FileHeader::writeFile2File(FILE* fileHandle)
{
	FILE* localFile = fopen(m_fileNamePath->c_str(), "rb");
	uint32 leftSize = m_fileSize;
	uint32 sizePerOne = 1 * 1024 * 1024;	// Ò»´Î¶ÁÈ¡
	char* pchar;
	if (localFile != nullptr)
	{
		pchar = new char[sizePerOne];

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
		delete pchar;
	}
}

uint32 FileHeader::calcHeaderSize()
{
	return m_pathLen + sizeof(m_fileSize) + sizeof(m_fileOffset);
}

void FileHeader::writeHeader2File(FILE* fileHandle)
{
	fwrite(&m_pathLen, sizeof(m_pathLen), 1, fileHandle);
	fwrite(m_fileNamePath->c_str(), m_fileNamePath->length(), 1, fileHandle);
	fwrite(&m_fileOffset, sizeof(m_fileOffset), 1, fileHandle);
	fwrite(&m_fileSize, sizeof(m_fileSize), 1, fileHandle);
}

END_NAMESPACE_FILEARCHIVETOOL
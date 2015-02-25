#include "ArchiveData.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include "FileInfo.h"
#include "Version.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveData::ArchiveData() : 
	m_version(ARCHIVETOOL_VERSION)
{
	m_pFileVec = new FileHeaderVec();
}

ArchiveData::~ArchiveData()
{
	clearFileVec();
	delete m_pFileVec;
}

void ArchiveData::ArchiveDir(const char* pDir)
{
	clearFileVec();
	//FileArchiveToolSysDef->getUtilPtr()->bindWalkDirDelegate(fastdelegate::MakeDelegate(this, &ArchiveData::fileHandle));
	FileArchiveToolSysDef->getUtilPtr()->getWalkDirDelegatePtr()->bind(this, &ArchiveData::fileHandle);
	FileArchiveToolSysDef->getUtilPtr()->walkDir(pDir);

	writeFile();
}

bool ArchiveData::fileHandle(struct _finddata_t* FileInfo)
{
	FileHeader* pFileHeader = new FileHeader();
	m_pFileVec->push_back(pFileHeader);

	(*(pFileHeader->m_fileNamePath)) = FileInfo->name;
	pFileHeader->m_fileSize = FileInfo->size;
	pFileHeader->m_fileOffset = m_fileSize;
	pFileHeader->m_pathLen = pFileHeader->m_fileNamePath->length();

	++m_fileCount;
	m_fileSize += FileInfo->size;
	return true;
}

void ArchiveData::clearFileVec()
{
	m_fileCount = 0;
	m_fileSize = 0;

	FileHeaderVecIt itBegin = m_pFileVec->begin();
	FileHeaderVecIt itEnd = m_pFileVec->end();
	for (; itBegin != itEnd; ++itBegin)
	{
		delete (*itBegin);
	}

	m_pFileVec->clear();
}

// 写入文件
void ArchiveData::writeFile()
{
	FILE* fileHandle = fopen("E:\\aaa.txt", "wb");

	if (fileHandle != nullptr)
	{
		// 写入版本
		fwrite(&m_version, sizeof(uint32), 1, fileHandle);
		// 写入文件数量
		fwrite(&m_fileCount, sizeof(uint32), 1, fileHandle);
		// 写入头部
		FileHeaderVecIt itBegin = m_pFileVec->begin();
		FileHeaderVecIt itEnd = m_pFileVec->end();
		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->writeHeader2File(fileHandle);
		}
		// 写文件内容
		itBegin = m_pFileVec->begin();
		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->writeFile2File(fileHandle);
		}

		fclose(fileHandle);
	}
}

END_NAMESPACE_FILEARCHIVETOOL
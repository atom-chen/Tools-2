#include "ArchiveData.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include "FileInfo.h"
#include "Version.h"
#include "SystemEndian.h"
#include "MByteBuffer.h"
#include "BufferDefaultValue.h"
#include "ArchiveTask.h"
#include "TaskQueue.h"
#include "ArchiveParam.h"
#include "UnArchiveParam.h"
#include "UnArchiveTask.h"
#include "Config.h"
#include "ArchiveHeader.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveData::ArchiveData()
{
	m_pArchiveHeader = new ArchiveHeader();
	m_pFileVec = new FileHeaderVec();
}

ArchiveData::~ArchiveData()
{
	delete m_pArchiveHeader;
	clearFileVec();
	delete m_pFileVec;
}

void ArchiveData::ArchiveDir()
{
	ArchiveTask* pArchiveTask = new ArchiveTask(FileArchiveToolSysDef->getArchiveParamPtr());
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pArchiveTask);
}

void ArchiveData::asyncArchiveDir(ArchiveParam* pArchiveParam)
{
	clearFileVec();
	//FileArchiveToolSysDef->getUtilPtr()->bindWalkDirDelegate(fastdelegate::MakeDelegate(this, &ArchiveData::fileHandle));
	FileArchiveToolSysDef->getUtilPtr()->getWalkDirDelegatePtr()->bind(this, &ArchiveData::fileHandle);
	FileArchiveToolSysDef->getUtilPtr()->walkDir(pArchiveParam->getArchiveDir());
	writeFile2ArchiveFile(pArchiveParam);
}

void ArchiveData::unArchiveFile()
{
	UnArchiveTask* pUnArchiveTask = new UnArchiveTask(FileArchiveToolSysDef->getUnArchiveParamPtr());
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pUnArchiveTask);
}

void ArchiveData::asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam)
{
	clearFileVec();
	writeArchiveFile2File(pUnArchiveParam);
}

bool ArchiveData::fileHandle(const char* walkPath, struct _finddata_t* FileInfo)
{
	FileHeader* pFileHeader = new FileHeader();
	m_pFileVec->push_back(pFileHeader);

	pFileHeader->setFullPath(walkPath, FileInfo->name);
	pFileHeader->setFileName(FileInfo->name);
	pFileHeader->modifyArchiveFileName(FileArchiveToolSysDef->getArchiveParamPtr());

	++m_pArchiveHeader->m_fileCount;
	m_fileSize += FileInfo->size;
	return true;
}

void ArchiveData::adjustHeaderOffset()
{
	calcHeaderSize(m_pArchiveHeader->m_headerSize);

	FileHeaderVecIt itBegin;
	FileHeaderVecIt itEnd;

	itBegin = m_pFileVec->begin();
	itEnd = m_pFileVec->end();

	uint32 curFileOffset = m_pArchiveHeader->m_headerSize;

	for (; itBegin != itEnd; ++itBegin)
	{
		(*itBegin)->adjustHeaderOffset(curFileOffset);
		curFileOffset += (*itBegin)->getFileSize();
	}
}

void ArchiveData::calcHeaderSize(uint32& headerSize)
{
	headerSize = m_pArchiveHeader->calcArchiveHeaderSizeNoFileHeader();

	FileHeaderVecIt itBegin;
	FileHeaderVecIt itEnd;

	itBegin = m_pFileVec->begin();
	itEnd = m_pFileVec->end();

	for (; itBegin != itEnd; ++itBegin)
	{
		headerSize += (*itBegin)->calcHeaderSize();
	}
}

void ArchiveData::clearFileVec()
{
	m_fileSize = 0;
	m_pArchiveHeader->clear();

	FileHeaderVecIt itBegin = m_pFileVec->begin();
	FileHeaderVecIt itEnd = m_pFileVec->end();
	for (; itBegin != itEnd; ++itBegin)
	{
		delete (*itBegin);
	}

	m_pFileVec->clear();
}

// 写入文件
void ArchiveData::writeFile2ArchiveFile(ArchiveParam* pArchiveParam)
{
	FILE* fileHandle = fopen(pArchiveParam->getArchiveFilePath(), "wb");

	if (fileHandle != nullptr)
	{
		calcHeaderSize(m_pArchiveHeader->m_headerSize);
		m_pArchiveHeader->writeArchiveFileHeader(fileHandle);

		// 移动文件指针
		fseek(fileHandle, m_pArchiveHeader->m_headerSize, SEEK_SET);	// 移动到文件开始位置

		FileHeaderVecIt itBegin;
		FileHeaderVecIt itEnd;

		itEnd = m_pFileVec->end();

		// 写文件内容
		itBegin = m_pFileVec->begin();
		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->writeFile2ArchiveFile(fileHandle);
		}

		// 移动文件指针
		fseek(fileHandle, m_pArchiveHeader->calcArchiveHeaderSizeNoFileHeader(), SEEK_SET);	// 移动到文件开始位置

		// 修正文件偏移
		adjustHeaderOffset();

		// 写入头部
		itBegin = m_pFileVec->begin();

		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->writeHeader2ArchiveFile(fileHandle);
		}

		fflush(fileHandle);
		fclose(fileHandle);
	}
}

void ArchiveData::readArchiveFileHeader(const char* pFileName)
{
	FILE* fileHandle = fopen(pFileName, "rb");

	if (fileHandle != nullptr)
	{
		readArchiveFileHeader(fileHandle);
		fclose(fileHandle);
	}
}

void ArchiveData::readArchiveFileHeader(FILE* fileHandle)
{
	MByteBuffer* pMByteBuffer = new MByteBuffer(INIT_CAPACITY);

	if (m_pArchiveHeader->readArchiveFileHeader(fileHandle, pMByteBuffer))		// 检查 magic
	{
		FileHeader* pFileHeader;
		for (uint32 idx = 0; idx < m_pArchiveHeader->m_fileCount; ++idx)
		{
			pFileHeader = new FileHeader();
			m_pFileVec->push_back(pFileHeader);
			pFileHeader->readHeaderFromArchiveFile(pMByteBuffer);
		}
	}
}

void ArchiveData::writeArchiveFile2File(UnArchiveParam* pUnArchiveParam)
{
	FILE* fileHandle = fopen(pUnArchiveParam->getUnArchiveFilePath(), "rb");

	if (fileHandle != nullptr)
	{
		readArchiveFileHeader(fileHandle);

		FileHeaderVecIt itBegin;
		FileHeaderVecIt itEnd;

		// 写入头部
		itBegin = m_pFileVec->begin();
		itEnd = m_pFileVec->end();

		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->writeArchiveFile2File(fileHandle, pUnArchiveParam);
		}

		fclose(fileHandle);
	}
}

END_NAMESPACE_FILEARCHIVETOOL
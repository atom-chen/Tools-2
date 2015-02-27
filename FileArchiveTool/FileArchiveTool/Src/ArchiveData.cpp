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

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveData::ArchiveData() : 
	m_version(ARCHIVETOOL_VERSION)
{
	m_magic[0] = 'a';
	m_magic[1] = 's';
	m_magic[2] = 'd';
	m_magic[3] = 'f';

	m_endian = sSysEndian;		// 0 大端 1 小端

	m_pFileVec = new FileHeaderVec();
}

ArchiveData::~ArchiveData()
{
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

	strcat(pFileHeader->m_pFullPath, walkPath);
	strcat(pFileHeader->m_pFullPath, "/");
	strcat(pFileHeader->m_pFullPath, FileInfo->name);

	strcpy(pFileHeader->m_fileNamePath, FileInfo->name);
	//pFileHeader->m_fileSize = FileInfo->size;
	//pFileHeader->m_fileOffset = m_fileSize;
	pFileHeader->modifyArchiveFileName(FileArchiveToolSysDef->getArchiveParamPtr());
	pFileHeader->m_pathLen = strlen(pFileHeader->m_fileNamePath);

	++m_fileCount;
	m_fileSize += FileInfo->size;
	return true;
}

void ArchiveData::adjustHeaderOffset()
{
	calcHeaderSize(m_headerSize);

	FileHeaderVecIt itBegin;
	FileHeaderVecIt itEnd;

	itBegin = m_pFileVec->begin();
	itEnd = m_pFileVec->end();

	uint32 curFileOffset = m_headerSize;

	for (; itBegin != itEnd; ++itBegin)
	{
		(*itBegin)->adjustHeaderOffset(curFileOffset);
		curFileOffset += (*itBegin)->getFileSize();
	}
}

void ArchiveData::calcHeaderSize(uint32& headerSize)
{
	headerSize = calcArchiveHeaderSizeNoFileHeader();

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
	m_fileCount = 0;
	m_fileSize = 0;
	m_headerSize = 0;

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
		// 写入 magic 
		fwrite(m_magic, sizeof(m_magic), 1, fileHandle);
		// 写入 endian 
		fwrite(&m_endian, sizeof(m_endian), 1, fileHandle);

		// 写入头部总共大小
		calcHeaderSize(m_headerSize);
		fwrite(&m_headerSize, sizeof(m_headerSize), 1, fileHandle);

		// 写入版本
		fwrite(&m_version, sizeof(m_version), 1, fileHandle);
		// 写入文件数量
		fwrite(&m_fileCount, sizeof(m_fileCount), 1, fileHandle);

		// 移动文件指针
		fseek(fileHandle, m_headerSize, SEEK_SET);	// 移动到文件开始位置

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
		fseek(fileHandle, calcArchiveHeaderSizeNoFileHeader(), SEEK_SET);	// 移动到文件开始位置

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

	// 读取 magic 
	fread(m_magic, sizeof(m_magic), 1, fileHandle);
	if (strncmp(m_magic, "asdf", sizeof(m_magic)) == 0)		// 检查 magic
	{
		// 读取 endian 
		fread(&m_endian, sizeof(m_endian), 1, fileHandle);
		pMByteBuffer->setEndian((SysEndian)m_endian);

		// 读取头部大小
		pMByteBuffer->setSize(sizeof(m_headerSize));		// 必然够 sizeof(m_headerSize) 个字节
		fread((void*)(pMByteBuffer->getStorage()), sizeof(m_headerSize), 1, fileHandle);
		pMByteBuffer->readUnsignedInt32(m_headerSize);
		pMByteBuffer->clear();

		pMByteBuffer->setSize(m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize));
		fread((void*)(pMByteBuffer->getStorage()), m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize), 1, fileHandle);

		// 读取版本
		pMByteBuffer->readUnsignedInt32(m_version);
		// 读取文件数量
		pMByteBuffer->readUnsignedInt32(m_fileCount);

		FileHeader* pFileHeader;
		for (uint32 idx = 0; idx < m_fileCount; ++idx)
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
	}
}

uint32 ArchiveData::calcArchiveHeaderSizeNoFileHeader()
{
	// 写入 magic 
	// 写入 endian 
	// 写入头部总共大小
	// 写入版本
	// 写入文件数量
	return sizeof(m_magic) + sizeof(m_endian) + sizeof(m_headerSize) + sizeof(m_version) + sizeof(m_fileCount);
}

END_NAMESPACE_FILEARCHIVETOOL
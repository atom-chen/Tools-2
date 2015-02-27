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

	m_endian = sSysEndian;		// 0 ��� 1 С��

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

// д���ļ�
void ArchiveData::writeFile2ArchiveFile(ArchiveParam* pArchiveParam)
{
	FILE* fileHandle = fopen(pArchiveParam->getArchiveFilePath(), "wb");

	if (fileHandle != nullptr)
	{
		// д�� magic 
		fwrite(m_magic, sizeof(m_magic), 1, fileHandle);
		// д�� endian 
		fwrite(&m_endian, sizeof(m_endian), 1, fileHandle);

		// д��ͷ���ܹ���С
		calcHeaderSize(m_headerSize);
		fwrite(&m_headerSize, sizeof(m_headerSize), 1, fileHandle);

		// д��汾
		fwrite(&m_version, sizeof(m_version), 1, fileHandle);
		// д���ļ�����
		fwrite(&m_fileCount, sizeof(m_fileCount), 1, fileHandle);

		// �ƶ��ļ�ָ��
		fseek(fileHandle, m_headerSize, SEEK_SET);	// �ƶ����ļ���ʼλ��

		FileHeaderVecIt itBegin;
		FileHeaderVecIt itEnd;

		itEnd = m_pFileVec->end();

		// д�ļ�����
		itBegin = m_pFileVec->begin();
		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->writeFile2ArchiveFile(fileHandle);
		}

		// �ƶ��ļ�ָ��
		fseek(fileHandle, calcArchiveHeaderSizeNoFileHeader(), SEEK_SET);	// �ƶ����ļ���ʼλ��

		// �����ļ�ƫ��
		adjustHeaderOffset();

		// д��ͷ��
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

	// ��ȡ magic 
	fread(m_magic, sizeof(m_magic), 1, fileHandle);
	if (strncmp(m_magic, "asdf", sizeof(m_magic)) == 0)		// ��� magic
	{
		// ��ȡ endian 
		fread(&m_endian, sizeof(m_endian), 1, fileHandle);
		pMByteBuffer->setEndian((SysEndian)m_endian);

		// ��ȡͷ����С
		pMByteBuffer->setSize(sizeof(m_headerSize));		// ��Ȼ�� sizeof(m_headerSize) ���ֽ�
		fread((void*)(pMByteBuffer->getStorage()), sizeof(m_headerSize), 1, fileHandle);
		pMByteBuffer->readUnsignedInt32(m_headerSize);
		pMByteBuffer->clear();

		pMByteBuffer->setSize(m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize));
		fread((void*)(pMByteBuffer->getStorage()), m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize), 1, fileHandle);

		// ��ȡ�汾
		pMByteBuffer->readUnsignedInt32(m_version);
		// ��ȡ�ļ�����
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

		// д��ͷ��
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
	// д�� magic 
	// д�� endian 
	// д��ͷ���ܹ���С
	// д��汾
	// д���ļ�����
	return sizeof(m_magic) + sizeof(m_endian) + sizeof(m_headerSize) + sizeof(m_version) + sizeof(m_fileCount);
}

END_NAMESPACE_FILEARCHIVETOOL
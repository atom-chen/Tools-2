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
#include "PakPathSplitInfo.h"
#include "PakItemBase.h"
#include "PakStatInfo.h"
#include "PakTask.h"
#include "PakItemDir.h"
#include "PakItemFileCopy.h"
#include "LogSys.h"
#include "LogStr.h"
#include "PakState.h"

#include <algorithm>

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveData::ArchiveData():
	m_curPak(nullptr)
{
	m_pPakItemVec = new PakItemVec;
	m_pPakPathSplitInfo = new PakPathSplitInfo;
	m_pPakStatInfo = new PakStatInfo;
}

ArchiveData::~ArchiveData()
{
	clearFileVec();
	delete m_pPakItemVec;
	delete m_pPakPathSplitInfo;
	delete m_pPakStatInfo;
}

void ArchiveData::ArchiveDir()
{
	FileArchiveToolSysDef->getPakStatePtr()->toggleState(ePS_PAKING);

	ArchiveTask* pArchiveTask = new ArchiveTask(FileArchiveToolSysDef->getArchiveParamPtr());
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pArchiveTask);
}

void ArchiveData::asyncArchiveDir(ArchiveParam* pArchiveParam)
{
	FileArchiveToolSysDef->getLogSysPtr()->log("======================\n");
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_START_SPLITPAK);

	clearFileVec();
	//FileArchiveToolSysDef->getUtilPtr()->bindWalkDirDelegate(fastdelegate::MakeDelegate(this, &ArchiveData::fileHandle));
	FileArchiveToolSysDef->getUtilPtr()->getWalkDirDelegatePtr()->bind(this, &ArchiveData::fileHandle);
	FileArchiveToolSysDef->getUtilPtr()->walkDir(pArchiveParam->getArchiveDir());

	addPakTask();	// 最后一个打包任务
	m_curPak = nullptr;
}

void ArchiveData::unArchiveFile()
{
	UnArchiveTask* pUnArchiveTask = new UnArchiveTask(FileArchiveToolSysDef->getUnArchiveParamPtr());
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pUnArchiveTask);
}

void ArchiveData::asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam)
{
	clearFileVec();
	m_curPak = new PakItemDir;
	addUnPakTask();
}

// 这个是将目录分成几个包
bool ArchiveData::fileHandle(const char* walkPath, struct _finddata_t* FileInfo)
{
	// 基本信息初始化
	std::string pathStr = walkPath;
	m_pPakPathSplitInfo->initInfo(pathStr, FileInfo);

	if (m_curPak == nullptr || !m_curPak->canAddFile(m_pPakPathSplitInfo))
	{
		addPakTask();
		newPakItem();
	}
	
	FileHeader* pFileHeader = new FileHeader();
	pFileHeader->initFileHeader(m_pPakPathSplitInfo);
	m_curPak->addFileHeader(pFileHeader);

	m_pPakStatInfo->addOneFile();
	m_pPakStatInfo->addOneFileSize(FileInfo->size);

	return true;
}

void ArchiveData::clearFileVec()
{
	m_pPakStatInfo->clear();

	PakItemVecIt itBegin = m_pPakItemVec->begin();
	PakItemVecIt itEnd = m_pPakItemVec->end();
	for (; itBegin != itEnd; ++itBegin)
	{
		delete (*itBegin);
	}

	m_pPakItemVec->clear();
}

void ArchiveData::newPakItem()
{
	if (m_pPakPathSplitInfo->getNeedPak())
	{
		if (m_curPak != nullptr)
		{
			if (m_curPak->isPakNameEqual(m_pPakPathSplitInfo->getPakName()))
			{
				m_pPakStatInfo->addCurPakIdx();
			}
			else
			{
				m_pPakStatInfo->clearCurPakIdx();
			}
		}
		m_curPak = new PakItemDir;
	}
	else
	{
		m_curPak = new PakItemFileCopy;
	}
	m_curPak->initByPakPathSplitInfo(m_pPakPathSplitInfo, m_pPakStatInfo->getCurPakIdx());
	m_pPakItemVec->push_back(m_curPak);
}

void ArchiveData::addPakTask()
{
	if (m_curPak != nullptr)		// 如果当前有 Pak ，就开始打包
	{
		m_curPak->ArchiveDir();
	}
}

void ArchiveData::addUnPakTask()
{
	if (m_curPak != nullptr)		// 如果当前有 Pak ，就开始打包
	{
		m_curPak->unArchiveFile();
	}
}

void ArchiveData::removePakItem(PakItemBase* pPakItem)
{
	int idx = 0;
	for (auto item : *m_pPakItemVec)
	{
		if (item == pPakItem)
		{
			PakItemVecIt ite = m_pPakItemVec->begin();
			std::advance(ite, idx);
			delete *ite;
			m_pPakItemVec->erase(ite);
			break;
		}

		++idx;
	}

	if (m_pPakItemVec->size() == 0)
	{
		FileArchiveToolSysDef->getLogSysPtr()->log(LS_PAK_END);
		FileArchiveToolSysDef->getLogSysPtr()->log("======================\n");
		FileArchiveToolSysDef->getPakStatePtr()->toggleState(ePS_PAKEND);
	}
}

void ArchiveData::removeUnPakItem(PakItemBase* pPakItem)
{
	delete m_curPak;
	m_curPak = nullptr;
}

size_t ArchiveData::getPakItemCount()
{
	return m_pPakItemVec->size();
}

END_NAMESPACE_FILEARCHIVETOOL
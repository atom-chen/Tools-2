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
#include "ManiFestData.h"
#include "PtrDefine.h"

#include <algorithm>

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveData::ArchiveData():
	m_curPak(nullptr), m_pCurParam(nullptr)
{
	m_pPakItemVec = new PakItemVec;
	m_pPakPathSplitInfo = new PakPathSplitInfo;
	m_pPakStatInfo = new PakStatInfo;
	m_pPakParamVec = new PakParamVec;
}

ArchiveData::~ArchiveData()
{
	clearFileVec();
	SAFE_DELETE(m_pPakItemVec);
	SAFE_DELETE(m_pPakPathSplitInfo);
	SAFE_DELETE(m_pPakStatInfo);
	SAFE_DELETE(m_pPakParamVec);
}

void ArchiveData::ArchiveDir()
{
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_SPLIT_LINE);
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_PAK_ADD_TASK);

	FileArchiveToolSysDef->getPakStatePtr()->toggleState(ePS_PAKING);

	ArchiveTask* pArchiveTask = new ArchiveTask(FileArchiveToolSysDef->getArchiveDataPtr()->getArchiveParamPtr());
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pArchiveTask);
}

void ArchiveData::asyncArchiveDir(ArchiveParam* pArchiveParam)
{
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_PAK_START_PAK_THREAD);
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
	FileArchiveToolSysDef->getLogSysPtr()->log("======================\n");
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_UNPAK_ADD_TASK);

	UnArchiveTask* pUnArchiveTask = new UnArchiveTask(getUnArchiveParamPtr());
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pUnArchiveTask);
}

void ArchiveData::asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam)
{
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_UNPAK_START_PAK_THREAD);

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

	if (m_curPak == nullptr || !m_pPakPathSplitInfo->getNeedPak() || !m_curPak->canAddFile(m_pPakPathSplitInfo))
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
		SAFE_DELETE(*itBegin);
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
		m_curPak->endOnePak();			// 结束当前包，以便设置一些数据
		m_curPak->ArchiveDir();			// 添加到线程，进行处理
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
			SAFE_DELETE(*ite);
			m_pPakItemVec->erase(ite);
			break;
		}

		++idx;
	}

	if (m_pPakItemVec->size() == 0)
	{
		FileArchiveToolSysDef->getLogSysPtr()->log("文件打包完成，开启启动输出清单文件");
		FileArchiveToolSysDef->getManiFestDataPtr()->addSelf2TaskQueue();
	}
}

void ArchiveData::removeUnPakItem(PakItemBase* pPakItem)
{
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_UNPAK_END);
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_SPLIT_LINE);

	SAFE_DELETE(m_curPak);
	m_curPak = nullptr;

	removeUnArchiveParamPtr();
	if (hasNextPakParam())
	{
		handleNextPakParam();
	}
}

void ArchiveData::onManiFestEnd()
{
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_PAK_END);
	FileArchiveToolSysDef->getLogSysPtr()->log(LS_SPLIT_LINE);
	FileArchiveToolSysDef->getPakStatePtr()->toggleState(ePS_PAKEND);

	removeArchiveParamPtr();
	if (hasNextPakParam())
	{
		handleNextPakParam();
	}
}

size_t ArchiveData::getPakItemCount()
{
	return m_pPakItemVec->size();
}

ArchiveParam* ArchiveData::getArchiveParamPtr()
{
	if (m_pPakParamVec->size() > 0)
	{
		if ((*m_pPakParamVec)[0]->getPakParamType() == ePP_Pak)
		{
			return static_cast<ArchiveParam*>((*m_pPakParamVec)[0]);
		}
	}

	return nullptr;
}

UnArchiveParam* ArchiveData::getUnArchiveParamPtr()
{
	if (m_pPakParamVec->size() > 0)
	{
		if ((*m_pPakParamVec)[0]->getPakParamType() == ePP_UnPak)
		{
			return static_cast<UnArchiveParam*>((*m_pPakParamVec)[0]);
		}
	}

	return nullptr;
}

void ArchiveData::addArchiveParamPtr(ArchiveParam* pArchiveParam)
{
	m_pPakParamVec->push_back(pArchiveParam);
	handleNextPakParam();
}

void ArchiveData::addUnArchiveParamPtr(UnArchiveParam* pUnArchiveParam)
{
	m_pPakParamVec->push_back(pUnArchiveParam);
	handleNextPakParam();
}

void ArchiveData::removeArchiveParamPtr()
{
	if (m_pPakParamVec->size() > 0)
	{
		if ((*m_pPakParamVec)[0]->getPakParamType() == ePP_Pak)
		{
			PakParamVecIt ite = m_pPakParamVec->begin();
			SAFE_DELETE(*ite);
			m_pPakParamVec->erase(ite);
		}
	}

	m_pCurParam = nullptr;
}

void ArchiveData::removeUnArchiveParamPtr()
{
	if (m_pPakParamVec->size() > 0)
	{
		if ((*m_pPakParamVec)[0]->getPakParamType() == ePP_UnPak)
		{
			PakParamVecIt ite = m_pPakParamVec->begin();
			SAFE_DELETE(*ite);
			m_pPakParamVec->erase(ite);
		}
	}

	m_pCurParam = nullptr;
}

void ArchiveData::handleNextPakParam()
{
	if (m_pCurParam == nullptr)		// 如果只有当前一个
	{
		m_pCurParam = (*m_pPakParamVec)[0];
		if (m_pCurParam->getPakParamType() == ePP_Pak)
		{
			ArchiveDir();
		}
		else if (m_pCurParam->getPakParamType() == ePP_UnPak)
		{
			unArchiveFile();
		}
	}
}

bool ArchiveData::hasNextPakParam()
{
	return (m_pPakParamVec->size() > 0);
}

END_NAMESPACE_FILEARCHIVETOOL
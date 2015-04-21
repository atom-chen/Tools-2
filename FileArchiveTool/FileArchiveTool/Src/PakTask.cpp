#include "PakTask.h"
#include "PakItemBase.h"
#include "FileArchiveToolSys.h"
#include "ArchiveData.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakTask::PakTask(PakItemBase* pPakItem, ArchiveParam* pArchiveParam)
{
	m_pPakItem = pPakItem;
	m_pArchiveParam = pArchiveParam;
}

PakTask::~PakTask()
{

}

bool PakTask::exeTask()
{
	m_pPakItem->asyncArchiveDir(m_pArchiveParam);
	return true;
}

bool PakTask::exeResult()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->removePakItem(m_pPakItem);
	m_pPakItem = nullptr;
	return true;
}

UnPakTask::UnPakTask(PakItemBase* pPakItem, UnArchiveParam* pUnArchiveParam)
{
	m_pPakItem = pPakItem;
	m_pUnArchiveParam = pUnArchiveParam;
}

UnPakTask::~UnPakTask()
{

}

bool UnPakTask::exeTask()
{
	m_pPakItem->asyncUnArchiveFile(m_pUnArchiveParam);
	return true;
}

bool UnPakTask::exeResult()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->removeUnPakItem(m_pPakItem);
	m_pPakItem = nullptr;
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL
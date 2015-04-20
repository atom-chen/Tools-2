#include "PakTask.h"
#include "PakItemBase.h"
#include "FileArchiveToolSys.h"
#include "ArchiveData.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakTask::PakTask(PakItemBase* pPakItem)
{
	m_pPakItem = pPakItem;
}

PakTask::~PakTask()
{

}

bool PakTask::exeTask()
{
	m_pPakItem->asyncArchiveDir(nullptr);
	return true;
}

bool PakTask::exeResult()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->removePakItem(m_pPakItem);
	m_pPakItem = nullptr;
	return true;
}

UnPakTask::UnPakTask(PakItemBase* pPakItem)
{
	m_pPakItem = pPakItem;
}

UnPakTask::~UnPakTask()
{

}

bool UnPakTask::exeTask()
{
	m_pPakItem->asyncUnArchiveFile(nullptr);
	return true;
}

bool UnPakTask::exeResult()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->removeUnPakItem(m_pPakItem);
	m_pPakItem = nullptr;
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL
#include "PakTask.h"
#include "PakItem.h"
#include "FileArchiveToolSys.h"
#include "ArchiveData.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakTask::PakTask(PakItem* pPakItem)
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

END_NAMESPACE_FILEARCHIVETOOL
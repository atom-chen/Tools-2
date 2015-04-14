#include "PakTask.h"
#include "PakItem.h"

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
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL
#include "ArchiveTask.h"
#include "FileArchiveToolSys.h"
#include "ArchiveData.h"
#include "ArchiveParam.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveTask::ArchiveTask(ArchiveParam* m_pArchiveParam)
{
	m_pArchiveParam = m_pArchiveParam;
}

ArchiveTask::~ArchiveTask()
{
	
}

bool ArchiveTask::exeTask()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->asyncArchiveDir(m_pArchiveParam);
	return true;
}

bool ArchiveTask::exeResult()
{
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL
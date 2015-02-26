#include "UnArchiveTask.h"
#include "FileArchiveToolSys.h"
#include "ArchiveData.h"
#include "UnArchiveParam.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

UnArchiveTask::UnArchiveTask(UnArchiveParam* pUnArchiveParam)
{
	m_pUnArchiveParam = pUnArchiveParam;
}

UnArchiveTask::~UnArchiveTask()
{
	
}

bool UnArchiveTask::exeTask()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->asyncUnArchiveFile(m_pUnArchiveParam);
	return true;
}

bool UnArchiveTask::exeResult()
{
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL
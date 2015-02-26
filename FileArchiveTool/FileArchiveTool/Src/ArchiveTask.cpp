#include "ArchiveTask.h"
#include "FileArchiveToolSys.h"
#include "ArchiveData.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveTask::ArchiveTask(const char* pPath)
{
	m_pPath = new char[strlen(pPath) + 1];
	m_pPath[strlen(pPath)] = 0;
	strncpy(m_pPath, pPath, strlen(pPath));
}

ArchiveTask::~ArchiveTask()
{
	delete[]m_pPath;
}

bool ArchiveTask::exeTask()
{
	FileArchiveToolSysDef->getArchiveDataPtr()->asyncArchiveDir(m_pPath);
	return true;
}

bool ArchiveTask::exeResult()
{
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL
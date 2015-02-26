#ifndef __ArchiveTask_H
#define __ArchiveTask_H

#include "ITask.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT ArchiveTask : public ITask
{
protected:
	char* m_pPath;

public:
	ArchiveTask(const char* pPath);
	~ArchiveTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
#ifndef __ArchiveTask_H
#define __ArchiveTask_H

#include "ITask.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ArchiveParam;

class FILEARCHIVETOOL_EXPORT ArchiveTask : public ITask
{
protected:
	ArchiveParam* m_pArchiveParam;

public:
	ArchiveTask(ArchiveParam* m_pArchiveParam);
	~ArchiveTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
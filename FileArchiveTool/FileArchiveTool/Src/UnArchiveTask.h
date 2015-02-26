#ifndef __UnArchiveTask_H
#define __UnArchiveTask_H

#include "ITask.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class UnArchiveParam;

class FILEARCHIVETOOL_EXPORT UnArchiveTask : public ITask
{
protected:
	UnArchiveParam* m_pUnArchiveParam;

public:
	UnArchiveTask(UnArchiveParam* m_pUnArchiveParam);
	~UnArchiveTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
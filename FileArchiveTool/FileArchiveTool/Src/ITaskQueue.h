#ifndef __ITaskQueue_H
#define __ITaskQueue_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ITask;

class FILEARCHIVETOOL_EXPORT ITaskQueue
{
public:
	virtual ITask* removeTask() = 0;
	virtual void addResult(ITask* task) = 0;
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
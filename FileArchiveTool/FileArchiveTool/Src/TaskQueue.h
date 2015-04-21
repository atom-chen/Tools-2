#ifndef __TaskQueue_H
#define __TaskQueue_H

#include "Prerequisites.h"

#include "LockQueue.h"
#include "ITaskQueue.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ITask;
class TaskThread;

class FILEARCHIVETOOL_EXPORT TaskQueue : public ITaskQueue
{
protected:
	LockQueue<ITask*>* m_pTaskQueue;
	LockQueue<ITask*>* m_pResultQueue;

public:
	TaskQueue();
	~TaskQueue();

	void addTask(ITask* task);
	virtual ITask* removeTask();

	virtual void addResult(ITask* task);
	ITask* removeResult();

	void endTask();
	void onTick();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
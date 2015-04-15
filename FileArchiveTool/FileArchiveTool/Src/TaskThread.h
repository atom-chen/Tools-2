#ifndef __TASK_THREAD_H
#define __TASK_THREAD_H

#include <boost/thread.hpp>
#include <set>

#include "Thread.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ITaskQueue;
class MCondition;

class TaskThread : public Thread
{
protected:
	ITaskQueue* m_pTaskQueue;
	MCondition* m_pMCondition;

public:
	TaskThread(ITaskQueue* pTaskQueue);
	virtual ~TaskThread();

	void setTaskQueue(ITaskQueue* pTaskQueue);
	void notifyNotEmpty();
	bool notifySelf();

private:
    virtual void run();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
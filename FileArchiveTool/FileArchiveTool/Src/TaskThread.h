#ifndef __TASK_THREAD_H
#define __TASK_THREAD_H

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <set>

#include "Thread.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ITaskQueue;

class TaskThread : public Thread
{
protected:
	ITaskQueue* m_pTaskQueue;
	boost::mutex* m_NotifyLock;
	boost::condition* m_pNotifyCond;

public:
	TaskThread(ITaskQueue* pTaskQueue);
	virtual ~TaskThread();

	void setTaskQueue(ITaskQueue* pTaskQueue);
	void notifyNotEmpty();

private:
    virtual void run();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
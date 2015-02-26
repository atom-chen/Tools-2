#ifndef __TASK_THREAD_H
#define __TASK_THREAD_H

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <set>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ITaskQueue;

class TaskThread : public boost::noncopyable
{
protected:
	ITaskQueue* m_pTaskQueue;
	boost::mutex* m_NotifyLock;
	boost::condition* m_pNotifyCond;

public:
	TaskThread(ITaskQueue* pTaskQueue);
	virtual ~TaskThread();

    void Stop();
    void Start();
    void Wait();

	void setExitFlag(bool exit);
	void setTaskQueue(ITaskQueue* pTaskQueue);

	void notifyNotEmpty();

private:
    virtual void loop();
    std::auto_ptr<boost::thread> m_thread;
	bool m_exitFlag;
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
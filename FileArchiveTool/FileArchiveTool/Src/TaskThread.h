#ifndef __TASK_THREAD_H
#define __TASK_THREAD_H

#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <set>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class TaskThread : public boost::noncopyable
{
public:
	TaskThread();
	virtual ~TaskThread();

    void Stop();
    void Start();
    void Wait();

	void setExitFlag(bool exit);

private:
    virtual void loop();
    std::auto_ptr<boost::thread> m_thread;
	bool m_exitFlag;
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
#include "TaskThread.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskThread::TaskThread()
{
	
}

TaskThread::~TaskThread()
{
    Stop();
    Wait();
}

void TaskThread::Stop()
{
    Wait();
}

void TaskThread::Start()
{
	m_thread.reset(new boost::thread(boost::bind(&TaskThread::loop, this)));
}

void TaskThread::Wait()
{
    if(m_thread.get())
    {
        m_thread->join();
        m_thread.reset();
    }
}

void TaskThread::loop()
{
	
}

END_NAMESPACE_FILEARCHIVETOOL
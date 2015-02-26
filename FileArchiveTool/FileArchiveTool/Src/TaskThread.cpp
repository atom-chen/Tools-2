#include "TaskThread.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskThread::TaskThread()
 : m_exitFlag(false)
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
	while (!m_exitFlag)
	{

	}
}

void TaskThread::setExitFlag(bool exit)
{
	m_exitFlag = exit;
}

END_NAMESPACE_FILEARCHIVETOOL
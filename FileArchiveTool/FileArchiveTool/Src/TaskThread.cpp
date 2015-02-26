#include "TaskThread.h"
#include "ITaskQueue.h"
#include "ITask.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskThread::TaskThread(ITaskQueue* pTaskQueue)
 : m_exitFlag(false)
{
	m_pTaskQueue = pTaskQueue;

	m_NotifyLock = new boost::mutex;
	m_pNotifyCond = new boost::condition;
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
	ITask* task;
	while (!m_exitFlag)
	{
		if (m_pTaskQueue)
		{
			task = m_pTaskQueue->removeTask();
			if (task)
			{
				task->exeTask();
				m_pTaskQueue->addResult(task);
			}
			else
			{
				m_pNotifyCond->wait(*m_NotifyLock);	// ×èÈû
			}
		}
	}
}

void TaskThread::setExitFlag(bool exit)
{
	m_exitFlag = exit;
}

void TaskThread::setTaskQueue(ITaskQueue* pTaskQueue)
{
	m_pTaskQueue = pTaskQueue;
}

void TaskThread::notifyNotEmpty()
{
	m_pNotifyCond->notify_all();
}

END_NAMESPACE_FILEARCHIVETOOL
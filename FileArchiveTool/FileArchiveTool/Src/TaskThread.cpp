#include "TaskThread.h"
#include "ITaskQueue.h"
#include "ITask.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskThread::TaskThread(ITaskQueue* pTaskQueue)
{
	m_pTaskQueue = pTaskQueue;

	m_NotifyLock = new boost::mutex;
	m_pNotifyCond = new boost::condition;
}

TaskThread::~TaskThread()
{

}

void TaskThread::run()
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

void TaskThread::setTaskQueue(ITaskQueue* pTaskQueue)
{
	m_pTaskQueue = pTaskQueue;
}

void TaskThread::notifyNotEmpty()
{
	m_pNotifyCond->notify_all();
}

END_NAMESPACE_FILEARCHIVETOOL
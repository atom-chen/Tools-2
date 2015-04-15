#include "TaskThread.h"
#include "ITaskQueue.h"
#include "ITask.h"
#include "MCondition.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskThread::TaskThread(ITaskQueue* pTaskQueue)
{
	m_pTaskQueue = pTaskQueue;
	m_pMCondition = new MCondition;
}

TaskThread::~TaskThread()
{
	delete m_pMCondition;
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
				m_pMCondition->wait();
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
	m_pMCondition->notifyOne();
}

bool TaskThread::notifySelf()
{
	if (m_pMCondition->canEnterWait())
	{
		m_pMCondition->notifyOne();
		return true;
	}

	return false;
}

END_NAMESPACE_FILEARCHIVETOOL
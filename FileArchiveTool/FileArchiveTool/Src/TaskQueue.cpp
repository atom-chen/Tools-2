#include "TaskQueue.h"
#include "TaskThread.h"
#include "ITask.h"
#include "FileArchiveToolSys.h"
#include "ThreadPool.h"
#include "PtrDefine.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskQueue::TaskQueue()
{
	m_pTaskQueue = new LockQueue<ITask*>;
	m_pResultQueue = new LockQueue<ITask*>;
}

TaskQueue::~TaskQueue()
{
	SAFE_DELETE(m_pTaskQueue);
	SAFE_DELETE(m_pResultQueue);
}

void TaskQueue::addTask(ITask* task)
{
	m_pTaskQueue->push(task);
	FileArchiveToolSysDef->getThreadPoolPtr()->notifyIdleThread();
}

ITask* TaskQueue::removeTask()
{
	ITask* ret = m_pTaskQueue->pop();
	return ret;
}

void TaskQueue::addResult(ITask* task)
{
	m_pResultQueue->push(task);
}

ITask* TaskQueue::removeResult()
{
	ITask* ret = m_pResultQueue->pop();
	return ret;
}

void TaskQueue::endTask()
{
	FileArchiveToolSysDef->getThreadPoolPtr()->wait();
}

void TaskQueue::onTick()
{
	ITask* task = removeResult();
	if (task != nullptr)
	{
		task->exeResult();
		SAFE_DELETE(task);
	}
}

END_NAMESPACE_FILEARCHIVETOOL
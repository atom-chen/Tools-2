#include "TaskQueue.h"
#include "TaskThread.h"
#include "ITask.h"
#include "FileArchiveToolSys.h"
#include "ThreadPool.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskQueue::TaskQueue()
{
	m_pTaskQueue = new std::queue<ITask*>;
	m_pResultQueue = new std::queue<ITask*>;

	m_taskLock = new boost::mutex;
	m_resultLock = new boost::mutex;
}

TaskQueue::~TaskQueue()
{
	delete m_pTaskQueue;
	delete m_pResultQueue;

	delete m_taskLock;
	delete m_resultLock;
}

void TaskQueue::addTask(ITask* task)
{
	boost::lock_guard<boost::mutex> lock(*m_taskLock);
	m_pTaskQueue->push(task);
	FileArchiveToolSysDef->getThreadPoolPtr()->notifyIdleThread();
}

ITask* TaskQueue::removeTask()
{
	ITask* ret = nullptr;
	if (m_pTaskQueue->size())
	{
		boost::lock_guard<boost::mutex> lock(*m_taskLock);
		ret = m_pTaskQueue->front();
		m_pTaskQueue->pop();
	}

	return ret;
}

void TaskQueue::addResult(ITask* task)
{
	boost::lock_guard<boost::mutex> lock(*m_resultLock);
	m_pResultQueue->push(task);
}

ITask* TaskQueue::removeResult()
{
	ITask* ret = nullptr;
	if (m_pResultQueue->size())
	{
		boost::lock_guard<boost::mutex> lock(*m_resultLock);
		ret = m_pResultQueue->front();
		m_pResultQueue->pop();
	}

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
		delete task;
	}
}

END_NAMESPACE_FILEARCHIVETOOL
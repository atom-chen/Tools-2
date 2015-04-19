#include "ThreadPool.h"
#include "TaskThread.h"
#include "FileArchiveToolSys.h"
#include "ITaskQueue.h"
#include "TaskQueue.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ThreadPool::ThreadPool(uint32 numThread)
{
	m_numThread = numThread;
	m_numThread = 1;
	m_pThreadVec = new std::vector<TaskThread*>(m_numThread);
	//for (uint32 idx = 0; idx < m_numThread; ++idx)
	//{
	//	// 构造函数中千万不要引用全局变量，因为这个时候全局变量可能还在构造中
	//	(*m_pThreadVec)[idx] = new TaskThread(FileArchiveToolSysDef->getTaskQueuePtr());
	//	(*m_pThreadVec)[idx]->Start();
	//}
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::instanceThread()
{
	for (uint32 idx = 0; idx < m_numThread; ++idx)
	{
		(*m_pThreadVec)[idx] = new TaskThread(FileArchiveToolSysDef->getTaskQueuePtr());
		(*m_pThreadVec)[idx]->Start();
	}
}

void ThreadPool::wait()
{
	for (auto thread : *m_pThreadVec)
	{
		thread->setExitFlag(true);		// 设置结束标识
		thread->notifyNotEmpty();		// 通知一次，防止线程在等待中
		thread->Wait();
	}

	for (auto thread : *m_pThreadVec)
	{
		delete thread;
	}

	m_pThreadVec->clear();
	m_pThreadVec = nullptr;
}

void ThreadPool::notifyIdleThread()
{
	for (auto thread : *m_pThreadVec)
	{
		if (thread->notifySelf())       // 如果唤醒某个线程就退出，如果一个都没有唤醒，说明当前线程都比较忙，需要等待
		{
			break;
		}
	}
}

END_NAMESPACE_FILEARCHIVETOOL
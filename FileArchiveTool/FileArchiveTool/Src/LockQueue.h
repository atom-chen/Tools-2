#ifndef __LockQueue_H
#define __LockQueue_H

#include "Prerequisites.h"

#include "boost/thread/mutex.hpp"
#include <queue>

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
 *@brief 线程安全的队列，参数必须是指针类型，非指针类型的偏特化没有实现
 */
template <class T>
class FILEARCHIVETOOL_EXPORT LockQueue
{
protected:
	boost::mutex* m_lock;
	std::queue<T>* m_queue;

public:
	LockQueue();
	~LockQueue();

	void push(T item);
	bool Remove(T item);
	void clear();
	T pop();
};

template<class T>
LockQueue<T>::LockQueue()
{
	m_lock = new boost::mutex;
	m_queue = new std::queue<T>;
}

template<class T>
LockQueue<T>::~LockQueue()
{
	clear();
	delete m_lock;
	delete m_queue;
}

template<class T>
void LockQueue<T>::push(T item)
{
	boost::mutex::scoped_lock sl(*m_lock);
	m_queue->push(item);
}

template<class T>
bool LockQueue<T>::Remove(T pItem)
{
	boost::mutex::scoped_lock sl(*m_lock);
	int idx = 0;
	for (auto item : *m_vec)
	{
		if (item == pItem)
		{
			std::vector<T>::iterator ite = m_queue->begin();
			std::advance(ite, idx);
			m_queue->erase(ite);
		}

		++idx;
	}
}

template<class T>
void LockQueue<T>::clear()
{
	boost::mutex::scoped_lock sl(*m_lock);
	//for (T item : *m_queue)
	//{
	//	delete item;
	//}
	//m_queue->swap(queue<T>());
	T item;
	while (!m_queue->empty())
	{
		item = m_queue->front();
		delete item;
		m_queue->pop();
	}
}

template<class T>
T LockQueue<T>::pop()
{
	boost::mutex::scoped_lock sl(*m_lock);
	T ret = nullptr;
	if (m_queue->size())
	{
		ret = m_queue->front();
		m_queue->pop();
	}

	return ret;
}

END_NAMESPACE_FILEARCHIVETOOL

#endif
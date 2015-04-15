#ifndef __LockQueue_H
#define __LockQueue_H

#include "Prerequisites.h"

#include "boost/thread.hpp"
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
 *@brief 线程安全的队列
 */
template <class T>
class FILEARCHIVETOOL_EXPORT LockQueue
{
protected:
	boost::mutex* m_lock;
	std::vector<T>* m_vec;

public:
	LockQueue();
	~LockQueue();

	void Add(T item);
	bool Remove(T item);
};

template<class T>
LockQueue<T>::LockQueue()
{
	m_lock = new boost::mutex;
	m_vec = new std::vector<T>;
}

template<class T>
LockQueue<T>::~LockQueue()
{
	delete m_lock;
	delete m_vec;
}

template<class T>
void LockQueue<T>::Add(T item)
{
	boost::mutex::scoped_lock sl(*m_lock);
	m_vec->push(item);
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
			std::vector<T>::iterator ite = m_vec->begin();
			std::advance(ite, idx);
			m_vec->erase(ite);
		}

		++idx;
	}
}

END_NAMESPACE_FILEARCHIVETOOL

#endif
#include "LockQueue.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

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
#ifndef __LockList_H
#define __LockList_H

#include "Prerequisites.h"
#include "PtrDefine.h"
#include "boost/thread/mutex.hpp"
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
 *@brief 线程安全的队列，参数必须是指针类型，非指针类型的偏特化没有实现
 */
template <class T>
class FILEARCHIVETOOL_EXPORT LockList
{
protected:
	boost::mutex* m_lock;
	std::vector<T>* m_vec;

public:
	//LockList();
	//~LockList();

	//std::vector<T>* getVec();
	//void push_back(T item);
	//bool Remove(T item);
	//void clear();

	LockList()
	{
		m_lock = new boost::mutex;
		m_vec = new std::vector<T>;
	}

	~LockList()
	{
		clear();
		SAFE_DELETE(m_lock);
		SAFE_DELETE(m_vec);
	}

	std::vector<T>* getVec()
	{
		return m_vec;
	}

	void push_back(T item)
	{
		boost::mutex::scoped_lock sl(*m_lock);
		m_vec->push_back(item);
	}

	bool Remove(T pItem)
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

	void clear()
	{
		boost::mutex::scoped_lock sl(*m_lock);
		for (auto item : *m_vec)
		{
			SAFE_DELETE(item);
		}
		m_vec->clear();
	}

	size_t size()
	{
		boost::mutex::scoped_lock sl(*m_lock);
		return m_vec->size();
	}
};

//template<class T>
//LockList<T>::LockList()
//{
//	m_lock = new boost::mutex;
//	m_vec = new std::vector<T>;
//}
//
//template<class T>
//LockList<T>::~LockList()
//{
//	clear();
//	SAFE_DELETE(m_lock;
//	SAFE_DELETE(m_vec;
//}
//
//template<class T>
//std::vector<T>* LockList<T>::getVec()
//{
//	return m_vec;
//}
//
//template<class T>
//void LockList<T>::push_back(T item)
//{
//	boost::mutex::scoped_lock sl(*m_lock);
//	m_vec->push_back(item);
//}
//
//template<class T>
//bool LockList<T>::Remove(T pItem)
//{
//	boost::mutex::scoped_lock sl(*m_lock);
//	int idx = 0;
//	for (auto item : *m_vec)
//	{
//		if (item == pItem)
//		{
//			std::vector<T>::iterator ite = m_vec->begin();
//			std::advance(ite, idx);
//			m_vec->erase(ite);
//		}
//
//		++idx;
//	}
//}
//
//template<class T>
//void LockList<T>::clear()
//{
//	boost::mutex::scoped_lock sl(*m_lock);
//	for (auto item : *m_vec)
//	{
//		SAFE_DELETE(item;
//	}
//	m_vec->clear();
//}

END_NAMESPACE_FILEARCHIVETOOL

#endif
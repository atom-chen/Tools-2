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

END_NAMESPACE_FILEARCHIVETOOL

#endif
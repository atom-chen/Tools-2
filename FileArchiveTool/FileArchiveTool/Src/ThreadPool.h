#ifndef __ThreadPool_H
#define __ThreadPool_H

#include "Prerequisites.h"

#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class TaskThread;

class FILEARCHIVETOOL_EXPORT ThreadPool
{
protected:
	uint32 m_numThread;
	std::vector<TaskThread*>* m_pThreadVec;

public:
	ThreadPool(uint32 numThread);
	~ThreadPool();

	void wait();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
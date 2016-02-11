#include "MemPool.h"
#include "LuaCObject.h"

MemList::MemList(int type)
{

}

MemList::~MemList()
{
	for (auto ptr : m_memList)
	{
		delete ptr;
	}

	m_memList.clear();
}

void* MemList::newMem()
{
	if (m_memList.size() > 0)
	{
		m_retMem = m_memList.front();
		m_memList.pop_front();
	}
	else
	{
		if (MemType::MEM_OBJECT == m_type)
		{
			m_retMem = new LuaCObject();
		}
	}

	return m_retMem;
}

void MemList::deleteMem(void* ptr)
{
	if (m_count >= MAX_COUNT)
	{
		delete ptr;				// 直接释放
	}
	else
	{
		m_memList.push_back(ptr);
	}
}


//==============================================

MemPool::MemPool()
{
	m_type2ListMap[MemType::MEM_OBJECT] = new MemList(MemType::MEM_OBJECT);
}

MemPool::~MemPool()
{
	MemMapIte _beginIte = m_type2ListMap.begin();
	MemMapIte _endIte = m_type2ListMap.end();

	for (; _beginIte != _endIte; ++_beginIte)
	{
		delete _beginIte->second;
	}

	m_type2ListMap.clear();
}

void* MemPool::newMem(int type)
{
	if (m_type2ListMap.find(type) != m_type2ListMap.end())
	{
		return m_type2ListMap[type]->newMem();
	}

	return nullptr;
}

void MemPool::deleteMem(int type, void* ptr)
{
	if (m_type2ListMap.find(type) != m_type2ListMap.end())
	{
		m_type2ListMap[type]->deleteMem(ptr);
	}
	else
	{
		delete ptr;		// 如果查找不到直接释放资源
	}
}
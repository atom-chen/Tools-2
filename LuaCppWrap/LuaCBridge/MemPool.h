#ifndef __MemPool_H
#define __MemPool_H

#include <list>

#define MAX_COUNT 10		// 最大允许不释放的内存数量

/**
 *@brief 可以申请的内存类型
 */
namespace MemType
{
	enum
	{
		MEM_OBJECT,		// 对应 LuaCObject 类型
	};
}

/**
 *@brief 内存列表
 */
class MemList
{
protected:
	int m_type;
	int m_count;	// 当前列表中的内存数量
	std::list<void*> m_memList;

	void* m_retMem;

public:
	MemList(int type);
	~MemList();

	void* newMem();				// 申请一块内存
	void  deleteMem(void* ptr);		// 释放一块内存
};

//===================

#include <map>

/**
 *@brief 内存池，防止频繁分配释放内存，仅限单线程
 */
class MemPool
{
public:
	typedef std::map<int, MemList*>::iterator MemMapIte;

protected:
	std::map<int, MemList*> m_type2ListMap;
public:
	MemPool();
	~MemPool();

	void* newMem(int type);				// 申请一块内存
	void  deleteMem(int type, void* ptr);		// 释放一块内存
};

#endif
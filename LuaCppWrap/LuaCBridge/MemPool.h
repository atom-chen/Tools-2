#ifndef __MemPool_H
#define __MemPool_H

#include <list>

#define MAX_COUNT 10		// ��������ͷŵ��ڴ�����

/**
 *@brief ����������ڴ�����
 */
namespace MemType
{
	enum
	{
		MEM_OBJECT,		// ��Ӧ LuaCObject ����
	};
}

/**
 *@brief �ڴ��б�
 */
class MemList
{
protected:
	int m_type;
	int m_count;	// ��ǰ�б��е��ڴ�����
	std::list<void*> m_memList;

	void* m_retMem;

public:
	MemList(int type);
	~MemList();

	void* newMem();				// ����һ���ڴ�
	void  deleteMem(void* ptr);		// �ͷ�һ���ڴ�
};

//===================

#include <map>

/**
 *@brief �ڴ�أ���ֹƵ�������ͷ��ڴ棬���޵��߳�
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

	void* newMem(int type);				// ����һ���ڴ�
	void  deleteMem(int type, void* ptr);		// �ͷ�һ���ڴ�
};

#endif
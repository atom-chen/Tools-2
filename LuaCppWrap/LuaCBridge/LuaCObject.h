#ifndef __LuaCObject_H_
#define __LuaCObject_H_

#include "LuaCBase.h"

class LuaCTable;
class LuaCFunction;

/**
*@brief �ȼ� Lua Դ�����е� lua.h ��#define LUA_TNIL		0
*/
#define LUAC_TNONE			(-1)

#define LUAC_TNIL			0
#define LUAC_TBOOLEAN		1
#define LUAC_TLIGHTUSERDATA	2
#define LUAC_TNUMBER		3
#define LUAC_TSTRING		4
#define LUAC_TTABLE			5
#define LUAC_TFUNCTION		6
#define LUAC_TUSERDATA		7
#define LUAC_TTHREAD		8

#define LUAC_NUMTAGS		9

/**
 *@brief �ȼ� Lua Դ�����е� lobject.h
 */
class LuaCObject
{
public:
	int m_type;

	union
	{
		lua_Integer m_int;				// ����
		lua_Number m_float;				// ��������
		int m_bool;						// ��������
		const char* m_pChar;			// �ַ���
		void* m_pLightUserData;			// �������û����ݣ���Ҫ��ָ��
		void* m_pUserData;				// �û�����
		LuaCTable* m_pLuaCTable;		// ��
		LuaCFunction* m_pLuaCFunction;	// ����
	};

public:
	LuaCObject();
	~LuaCObject();
	int GetType();
};

#endif
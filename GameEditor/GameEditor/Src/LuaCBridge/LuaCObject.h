#ifndef __LuaCObject_H_
#define __LuaCObject_H_

#include "GameEditor.h"
#include "LuaCBase.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCTable;
class LuaCFunction;

/**
*@brief 等价 Lua 源代码中的 lua.h ，#define LUA_TNIL		0
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
 *@brief 等价 Lua 源代码中的 lobject.h
 */
class GAMEEDITOR_EXPORT LuaCObject
{
public:
	int m_type;

	union
	{
		lua_Integer m_int;				// 整形
		lua_Number m_float;				// 浮点类型
		int m_bool;						// 布尔类型
		const char* m_pChar;			// 字符串
		void* m_pLightUserData;			// 轻量级用户数据，主要是指针
		void* m_pUserData;				// 用户数据
		LuaCTable* m_pLuaCTable;		// 表
		LuaCFunction* m_pLuaCFunction;	// 函数
	};

public:
	LuaCObject();
	~LuaCObject();
	int GetType();
};

END_NAMESPACE_GAMEEDITOR

#endif
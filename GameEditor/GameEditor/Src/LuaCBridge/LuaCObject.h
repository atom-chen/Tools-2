#ifndef __LuaCObject_H_
#define __LuaCObject_H_

#include "GameEditor.h"

BEGIN_NAMESPACE_GAMEEDITOR

/**
*@brief 等价 Lua 源代码中的 lua.h ，#define LUA_TNIL		0
*/
#define LUAC_TNONE		(-1)

#define LUAC_TNIL		0
#define LUAC_TBOOLEAN		1
#define LUAC_TLIGHTUSERDATA	2
#define LUAC_TNUMBER		3
#define LUAC_TSTRING		4
#define LUAC_TTABLE		5
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
	LuaCObject();
	~LuaCObject();
};

END_NAMESPACE_GAMEEDITOR

#endif
#ifndef __LuaCTable_H_
#define __LuaCTable_H_

#include "GameEditor.h"
#include "lua.hpp"

BEGIN_NAMESPACE_GAMEEDITOR

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class GAMEEDITOR_EXPORT LuaCTable
{
public:
	LuaCTable();
	~LuaCTable();
};

END_NAMESPACE_GAMEEDITOR

#endif
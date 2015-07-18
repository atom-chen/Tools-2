#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "GameEditor.h"
#include "lua.hpp"

BEGIN_NAMESPACE_GAMEEDITOR

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class GAMEEDITOR_EXPORT LuaCVM
{
public:
	lua_State* m_L;

public:
	LuaCVM();
	~LuaCVM();

	void openLua();					// 创建 Lua 虚拟机
	void closeLua();				// 关闭 Lua 虚拟机
};

END_NAMESPACE_GAMEEDITOR

#endif
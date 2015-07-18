#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT LuaCScriptMgr
{
protected:
	lua_State* m_L;

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	void openLua();					// 创建 Lua 虚拟机
	void closeLua();				// 关闭 Lua 虚拟机
	void setLuaFilePath(std::string path);	// 设置 Lua 文件的查找目录
	void setCFilePath(std::string path);	// 设置 C 库的查找目录
};

END_NAMESPACE_GAMEEDITOR

#endif
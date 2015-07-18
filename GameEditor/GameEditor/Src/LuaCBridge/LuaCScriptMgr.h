#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;

class GAMEEDITOR_EXPORT LuaCScriptMgr
{
protected:
	LuaCVM* m_pLuaCVM;

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	void setLuaFilePath(std::string path);	// 设置 Lua 文件的查找目录
	void setCFilePath(std::string path);	// 设置 C 库的查找目录
};

END_NAMESPACE_GAMEEDITOR

#endif
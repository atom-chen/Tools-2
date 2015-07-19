#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>
#include "LuaCObject.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;
class LuaCObjectTranslator;

class GAMEEDITOR_EXPORT LuaCScriptMgr
{
public:
	static LuaCObjectTranslator* _translator;

protected:
	LuaCVM* m_pLuaCVM;

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	void setLuaFilePath(std::string path);	// 设置 Lua 文件的查找目录
	void setCFilePath(std::string path);	// 设置 C 库的查找目录

	static void CheckArgsCount(lua_State* L, int count);
	static LuaCObject* GetVarObject(lua_State* L, int stackPos);
	static LuaCObject* GetVarTable(lua_State* L, int stackPos);
	static void PushVarObject(lua_State* L, LuaCObject* o);
	static LuaCObjectTranslator* GetTranslator(lua_State* L);
};

END_NAMESPACE_GAMEEDITOR

#endif
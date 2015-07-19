#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>
#include <vector>
#include <map>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;
class LuaCObjectTranslator;
class LuaCBase;
class LuaCObject;
class LuaCFunction;

class GAMEEDITOR_EXPORT LuaCScriptMgr
{
public:
	static LuaCObjectTranslator* _translator;
#if MULTI_STATE
	static List<LuaScriptMgr*> mgrList;
	static int mgrPos = 0;
#else
	static LuaCFunction* traceback;
#endif

protected:
	LuaCVM* m_pLuaCVM;
#include "PushWarn.h"
	std::map<std::string, LuaCBase*> dict;
#include "PopWarn.h"

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	void setLuaFilePath(std::string path);	// 设置 Lua 文件的查找目录
	void setCFilePath(std::string path);	// 设置 C 库的查找目录
	std::vector<LuaCObject*> CallLuaFunction(std::string name, std::vector<LuaCObject*>& args);

	static void CheckArgsCount(lua_State* L, int count);
	static LuaCObject* GetVarObject(lua_State* L, int stackPos);
	static LuaCObject* GetVarTable(lua_State* L, int stackPos);
	static void PushVarObject(lua_State* L, LuaCObject* o);
	static LuaCObjectTranslator* GetTranslator(lua_State* L);
	static bool PushLuaFunction(lua_State* L, std::string fullPath);
	static void PushTraceBack(lua_State* L);
	static bool PushLuaTable(lua_State* L, std::string fullPath);
	static void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
};

END_NAMESPACE_GAMEEDITOR

#endif
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

class LuaMethod;
class LuaField;

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

	LuaCVM* getLuaCVM();

	void setLuaFilePath(std::string path);	// ���� Lua �ļ��Ĳ���Ŀ¼
	void setCFilePath(std::string path);	// ���� C ��Ĳ���Ŀ¼

	void doString(std::string value);
	void doFile(std::string path);
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
	static void RegisterLib(lua_State* L, std::string libName, std::string className, std::vector<LuaMethod*> regs, std::vector<LuaField*> fields, std::string baseClassName);
	static void CreateTable(lua_State* L, std::string fullPath);
	static int garbageCollection(lua_State* luaState);
};

END_NAMESPACE_GAMEEDITOR

#endif
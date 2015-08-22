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
class LuaCTable;

class GAMEEDITOR_EXPORT LuaCScriptMgr
{
public:
	static LuaCScriptMgr* Instance;
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
	typedef std::map<std::string, LuaCBase*>::iterator mapIte;
	std::map<std::string, LuaCBase*> dict;
	std::string luaIndex;
	std::string luaNewIndex;
	std::string luaTableCall;
	std::string luaEnumIndex;
#include "PopWarn.h"

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	LuaCVM* getLuaCVM();

	void setLuaFilePath(std::string path);	// 设置 Lua 文件的查找目录
	void setCFilePath(std::string path);	// 设置 C 库的查找目录

	void doString(std::string value);
	void doFile(std::string path);
	std::vector<LuaCObject*> CallLuaFunction(std::string name, std::vector<LuaCObject*>& args);
	lua_State* GetL();
	void PrintLua(std::vector<std::string> param);
	void LuaGC(std::vector<std::string> param);
	void LuaMem(std::vector<std::string> param);
	LuaCFunction* GetLuaFunction(std::string name);
	int GetFunctionRef(std::string name);
	bool IsFuncExists(std::string name);
	LuaCTable* GetLuaTable(std::string tableName);
	void RemoveLuaRes(std::string name);
	static double GetNumber(lua_State* L, int stackPos);
	static bool GetBoolean(lua_State* L, int stackPos);
	std::string GetString(lua_State* L, int stackPos);
	static LuaCFunction* GetFunction(lua_State* L, int stackPos);
	static LuaCFunction* ToLuaFunction(lua_State* L, int stackPos);
	static LuaCFunction* GetLuaFunction(lua_State* L, int stackPos);
	static LuaCTable* ToLuaTable(lua_State* L, int stackPos);
	static LuaCTable* GetTable(lua_State* L, int stackPos);
	static LuaCTable* GetLuaTable(lua_State* L, int stackPos);
	static LuaCObject* GetLuaObject(lua_State* L, int stackPos);

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
	static void ThrowLuaException(lua_State* L);
	static LuaCScriptMgr* GetMgrFromLuaState(lua_State* L);
	static void RegisterLib(lua_State* L, std::string libName, std::vector<LuaMethod*> regs);
	static void RegisterLib(lua_State* L, std::string libName, std::string className, std::vector<LuaMethod*> regs);
	static std::string GetLuaString(lua_State* L, int stackPos);
};

END_NAMESPACE_GAMEEDITOR

#endif
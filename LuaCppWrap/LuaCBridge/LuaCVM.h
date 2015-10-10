#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "lua.hpp"
#include <string>
#include <vector>
#include <map>

class LuaCObjectTranslator;
class LuaCObject;
class LuaCTable;
class LuaCFunction;
class LuaCScriptMgr;
class LuaCBase;
class LuaMethod;
class LuaField;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class LuaCVM
{
protected:
	typedef std::map<std::string, LuaCBase*>::iterator mapIte;
	std::map<std::string, LuaCBase*> m_dict;
	std::string m_luaIndex;
	std::string m_luaNewIndex;
	std::string m_luaTableCall;
	std::string m_luaEnumIndex;

public:
	lua_State* L;
	LuaCFunction* m_traceback;
	LuaCObjectTranslator* m_translator;

public:
	LuaCVM();
	~LuaCVM();

	void openLua();					// 创建 Lua 虚拟机
	void closeLua();				// 关闭 Lua 虚拟机

	void doString(std::string value);
	void doFile(std::string path);
	LuaCObject* getLuaObject(std::string fullPath);
	void setLuaObject(std::string fullPath, LuaCObject* value);
	LuaCObject* getObject(std::vector<std::string>& remainingPath);
	void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
	void setObject(std::vector<std::string>& remainingPath, LuaCObject* value);

	void NewTable(std::string fullPath);
	LuaCTable* NewTable();
	LuaCObject* rawGetObject(int reference, std::string field);
	LuaCObject* getObject(int reference, std::string field);
	LuaCObject* getObject(int reference, LuaCObject* field);
	void setObject(int reference, std::string field, LuaCObject* val);
	void setObject(int reference, LuaCObject* field, LuaCObject* val);
	LuaCFunction* RegisterFunction(std::string fullPath, lua_CFunction function);



	void setLuaFilePath(std::string path);	// 设置 Lua 文件的查找目录
	void setCFilePath(std::string path);	// 设置 C 库的查找目录

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
	double GetNumber(int stackPos);
	bool GetBoolean(int stackPos);
	std::string GetString(int stackPos);
	LuaCFunction* GetFunction(int stackPos);
	LuaCFunction* ToLuaFunction(int stackPos);
	LuaCFunction* GetLuaFunction(int stackPos);
	LuaCTable* ToLuaTable(int stackPos);
	LuaCTable* GetTable(int stackPos);
	LuaCTable* GetLuaTable(int stackPos);
	LuaCObject* GetLuaObject(int stackPos);

	void CheckArgsCount(int count);
	LuaCObject* GetVarObject(int stackPos);
	LuaCObject* GetVarTable(int stackPos);
	void PushVarObject(LuaCObject* o);
	LuaCObjectTranslator* GetTranslator();
	bool PushLuaFunction(std::string fullPath);
	void PushTraceBack();
	bool PushLuaTable(std::string fullPath);
	void RegisterLib(std::string libName, std::string className, std::vector<LuaMethod*> regs, std::vector<LuaField*> fields, std::string baseClassName);
	void CreateTable(std::string fullPath);
	static int garbageCollection(lua_State* L);
	void ThrowLuaException(lua_State* L);
	LuaCScriptMgr* GetMgrFromLuaState(lua_State* L);
	void RegisterLib(std::string libName, std::vector<LuaMethod*> regs);
	void RegisterLib(std::string libName, std::string className, std::vector<LuaMethod*> regs);
	std::string GetLuaString(int stackPos);
};

#endif
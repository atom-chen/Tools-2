#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "lua.hpp"
#include <string>
#include <vector>

class LuaCObjectTranslator;
class LuaCObject;
class LuaCTable;
class LuaCFunction;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class LuaCVM
{
public:
	lua_State* L;

public:
	LuaCObjectTranslator* translator;

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

	LuaCFunction* GetLuaFunction(std::string name);
	LuaCTable* GetLuaTable(std::string tableName);
};

#endif
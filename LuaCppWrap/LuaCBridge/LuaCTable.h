#ifndef __LuaCTable_H_
#define __LuaCTable_H_

#include "lua.hpp"
#include "LuaCBase.h"

class LuaCVM;
class LuaCObject;
class LuaCFunction;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class LuaCTable : public LuaCBase
{
public:
	LuaCTable(int reference, LuaCVM* interpreter);
	~LuaCTable();

	LuaCObject* getField(std::string field);
	void setField(std::string field, LuaCObject* value);
	void SetMetaTable(LuaCTable* metaTable);
	void Set(std::string key, LuaCObject* o);
	LuaCObject* rawget(std::string field);
	LuaCObject* rawgetFunction(std::string field);
	LuaCFunction* RawGetFunc(std::string field);
	void push(lua_State* luaState);
	std::string ToString();
	void setLuaFunction(std::string key, lua_CFunction func);
};

#endif
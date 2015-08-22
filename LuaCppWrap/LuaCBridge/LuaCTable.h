#ifndef __LuaCTable_H_
#define __LuaCTable_H_

#include "GameEditor.h"
#include "lua.hpp"
#include "LuaCBase.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;
class LuaCObject;
class LuaCFunction;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class GAMEEDITOR_EXPORT LuaCTable : public LuaCBase
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

END_NAMESPACE_GAMEEDITOR

#endif
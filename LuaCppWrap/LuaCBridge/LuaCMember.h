#ifndef __LuaCMember_H_
#define __LuaCMember_H_

#include <string>
#include "lua.hpp"

class LuaMethod
{
public:
	std::string name;
	lua_CFunction func;

public:
	LuaMethod(std::string str, lua_CFunction f);
};

class LuaField
{
public:
	std::string name;
	lua_CFunction getter;
	lua_CFunction setter;

public:
	LuaField(std::string str, lua_CFunction g, lua_CFunction s);
};

#endif
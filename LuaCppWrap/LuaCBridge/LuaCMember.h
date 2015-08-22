#ifndef __LuaCMember_H_
#define __LuaCMember_H_

#include "GameEditor.h"
#include <string>
#include "lua.hpp"

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT LuaMethod
{
public:
#include "PushWarn.h"
	std::string name;
#include "PopWarn.h"
	lua_CFunction func;

public:
	LuaMethod(std::string str, lua_CFunction f);
};

class GAMEEDITOR_EXPORT LuaField
{
public:
#include "PushWarn.h"
	std::string name;
#include "PopWarn.h"
	lua_CFunction getter;
	lua_CFunction setter;

public:
	LuaField(std::string str, lua_CFunction g, lua_CFunction s);
};

END_NAMESPACE_GAMEEDITOR

#endif
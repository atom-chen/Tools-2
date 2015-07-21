#include "LuaCMember.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaMethod::LuaMethod(std::string str, lua_CFunction f)
{
	name = str;
	func = f;
}

LuaField::LuaField(std::string str, lua_CFunction g, lua_CFunction s)
{
	name = str;
	getter = g;
	setter = s;
}

END_NAMESPACE_GAMEEDITOR
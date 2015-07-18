#include "LuaCVM.h"
#include "LuaCObjectTranslator.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCVM::LuaCVM()
{
	m_translator = new LuaCObjectTranslator;
	openLua();
}

LuaCVM::~LuaCVM()
{

}

void LuaCVM::openLua()
{
	/* initialize Lua */
	// m_L = lua_open();		// Lua5.1
	// m_L = lua_newstate();	// Lua5.3
	m_L = luaL_newstate();		// Lua5.3
	/* load Lua libraries */
	luaL_openlibs(m_L);
}

void LuaCVM::closeLua()
{
	lua_close(m_L);
}

LuaCObject LuaCVM::getLuaObject(std::string fullPath);
{
	LuaCObject returnValue = null;
	int oldTop = lua_gettop(L);
	std::vector<std::string> path;
	std::string delim = ".";
	split(fullPath, delim, &path);

	lua_getglobal(L, path[0]);
	returnValue = translator.getObject(L, -1);
	if (path.Length > 1)
	{
		string[] remainingPath = new string[path.Length - 1];
		Array.Copy(path, 1, remainingPath, 0, path.Length - 1);
		returnValue = getObject(remainingPath);
	}
	lua_settop(L, oldTop);
	return returnValue;
}

void LuaCVM::setLuaObject(std::string fullPath)
{
	int oldTop = LuaDLL.lua_gettop(L);
	std::vector<std::string> path;
	std::string delim = ".";
	split(fullPath, delim, &path);

	if (path.Length == 1)
	{
		translator.push(L, value);
		LuaDLL.lua_setglobal(L, fullPath);
	}
	else
	{
		//LuaDLL.lua_getglobal(L, path[0]);
		LuaDLL.lua_rawglobal(L, path[0]);
		LuaTypes type = LuaDLL.lua_type(L, -1);

		if (type == LuaTypes.LUA_TNIL)
		{
			Debugger.LogError("Table {0} not exists", path[0]);
			LuaDLL.lua_settop(L, oldTop);
			return;
		}

		string[] remainingPath = new string[path.Length - 1];
		Array.Copy(path, 1, remainingPath, 0, path.Length - 1);
		setObject(remainingPath, value);
	}

	LuaDLL.lua_settop(L, oldTop);
}

LuaCObject LuaCVM::getObject(std::vector<std::string>& remainingPath)
{
	object returnValue = null;
	for (int i = 0; i < remainingPath.Length; i++)
	{
		LuaDLL.lua_pushstring(L, remainingPath[i]);
		LuaDLL.lua_gettable(L, -2);
		returnValue = translator.getObject(L, -1);
		if (returnValue == null) break;
	}
	return returnValue;
}

//注意：当字符串为空时，也会返回一个空字符串  
void LuaCVM::split(std::string& s, std::string& delim, std::vector<std::string>* ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last>0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}

END_NAMESPACE_GAMEEDITOR
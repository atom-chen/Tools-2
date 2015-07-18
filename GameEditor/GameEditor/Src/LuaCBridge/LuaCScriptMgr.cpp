#include "LuaCScriptMgr.h"
#include <sstream>

BEGIN_NAMESPACE_GAMEEDITOR

LuaCScriptMgr::LuaCScriptMgr()
{
	openLua();
	setLuaFilePath("D:/file/opensource/unity-game-git/unitygame/Tools/GameEditor/LuaScript");
	luaL_dofile(m_L, "TestLua.lua");
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	closeLua();
}

void LuaCScriptMgr::openLua()
{
	/* initialize Lua */
	// m_L = lua_open();		// Lua5.1
	// m_L = lua_newstate();	// Lua5.3
	m_L = luaL_newstate();		// Lua5.3
	/* load Lua libraries */
	luaL_openlibs(m_L);
}

void LuaCScriptMgr::closeLua()
{
	lua_close(m_L);
}

void LuaCScriptMgr::setLuaFilePath(std::string path)
{
	std::stringstream strStream;
	strStream << "local m_package_path = package.path" << "\r\n" << "package.path = string.format(\"%s; %s / ? .lua\", m_package_path, " << path << ")";
	luaL_dostring(m_L, strStream.str().c_str());
}

void LuaCScriptMgr::setCFilePath(std::string path)
{

}

END_NAMESPACE_GAMEEDITOR
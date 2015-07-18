#include "LuaCVM.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCVM::LuaCVM()
{
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

END_NAMESPACE_GAMEEDITOR
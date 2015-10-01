#ifndef __LuaCTestWrap_H_
#define __LuaCTestWrap_H_

#include "lua.hpp"

class LuaCScriptMgr;

void LuaCTestWrap_Bind();
void testBind1f();
void testBind2f();
void testBind3f();
void testBind4f();
void testBind5f();
void testBind6f();
void testBind7f();
void testBind8f();
void testLoadLua();
int LuaCTestWrap_cHelloWorld(lua_State* L);
int LuaCTestWrap_cTableHelloWorld(lua_State* L);
int LuaCTestWrap_cppHelloWorld(lua_State* L);

extern LuaCScriptMgr* g_pLuaCScriptMgr;

#endif
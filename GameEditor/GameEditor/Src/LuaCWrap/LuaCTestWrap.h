#ifndef __LuaCTestWrap_H_
#define __LuaCTestWrap_H_

#include "GameEditor.h"
#include "lua.hpp"

BEGIN_NAMESPACE_GAMEEDITOR

void LuaCTestWrap_Bind();
void testBind1f();
void testBind2f();
void testBind3f();
void TestBind4f();
void TestBind5f();
int LuaCTestWrap_cHelloWorld(lua_State* L);
int LuaCTestWrap_cppHelloWorld(lua_State* L);

END_NAMESPACE_GAMEEDITOR

#endif
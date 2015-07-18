#ifndef __LuaCTestWrap_H_
#define __LuaCTestWrap_H_

#include "GameEditor.h"
#include "lua.hpp"

BEGIN_NAMESPACE_GAMEEDITOR

void LuaCTestWrap_Bind();
int LuaCTestWrap_sayHello(lua_State* L);

END_NAMESPACE_GAMEEDITOR

#endif
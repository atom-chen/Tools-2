#ifndef __LuaCustomLoader_H_
#define __LuaCustomLoader_H_

/**
 * @brief æﬂÃÂ≤Œ’’ loadlib.c
 */
#include "lua.hpp"

void loaderror(lua_State *L, const char *filename);
int lua_file_from_manual_func(lua_State *L);
void InitManualFunction(lua_State *L);

int MyLoader(lua_State* pState);
void AddLoader(lua_State *L);

#endif
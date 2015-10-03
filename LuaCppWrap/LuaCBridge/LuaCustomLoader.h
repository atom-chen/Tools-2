#ifndef __LuaCustomLoader_H_
#define __LuaCustomLoader_H_

/**
 * @brief æﬂÃÂ≤Œ’’ loadlib.c
 */
#include "lua.hpp"
#include <string>

void loaderror(lua_State *L, const char *filename);
int lua_file_from_manual_func(lua_State *L);
void InitManualFunction(lua_State *L);

extern std::string g_searchsRootPath;
int MyLoader(lua_State* pState);
void AddLoader(lua_State *L);
int loadLua(lua_State *L);

void dotAddLoader(lua_State *L);
int dotLoadLua(lua_State *L);
int traceback(lua_State *L);

#endif
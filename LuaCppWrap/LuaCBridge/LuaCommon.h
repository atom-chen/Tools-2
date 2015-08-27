#pragma once

// D:\ProgramFiles(x86)\Lua\5.1\include\lauxlib.h ，Lua5.3 中没有这个宏定义了
#define lua_getref(L,ref)       lua_rawgeti(L, LUA_REGISTRYINDEX, (ref))
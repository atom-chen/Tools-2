#include "LuaCustomLoader.h"
#include <string>
#include <string.h>
#include <stdio.h>

void loaderror(lua_State *L, const char *filename)
{
	luaL_error(L, "error loading module " LUA_QS " from file " LUA_QS ":\n\t%s",
		lua_tostring(L, 1), filename, lua_tostring(L, -1));
}

int lua_file_from_manual_func(lua_State *L)
{
	const char *filename = nullptr;
	const char *name = luaL_checkstring(L, 1);
	//filename = findfile(L, name, "path");
	if (filename == NULL) return 1;  /* library not found in this path */
	//if (manul_load_file && manul_load_file(L, filename) != 0)
	//	loaderror(L, filename);
	return 1;  /* library loaded successfully */
}

void InitManualFunction(lua_State *L)
{
	int type = 0;
	lua_getglobal(L, "package");
	type = lua_type(L, -1);
	//lua_getfield(L, -1, "loaders");	//lua5.1 package.loaders
	lua_getfield(L, -1, "searchers");	//lua5.3 package.searchers
	type = lua_type(L, -1);
	lua_pushnumber(L, 2);
	lua_gettable(L, -2);			//package.loader[2]
	lua_pushnumber(L, 2);			//先把索引压栈，用来设置C函数到这个索引位置
	lua_pushcfunction(L, MyLoader);	//压入自己的C函数
	lua_settable(L, -4);	//替换旧函数
	lua_pop(L, 3);			//清理堆栈
}

std::string g_searchsRootPath = "D:/file/opensource/unity-game-git/unitygame/Tools/LuaCppWrap/LuaScript";

int MyLoader(lua_State* pState)
{
	//const char *name = luaL_checkstring(pState, 1);
	std::string module = lua_tostring(pState, 1);
	module += ".lua";
	module = g_searchsRootPath + "/" + module;

	const char* fullPath = module.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "r");
	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	if (size > 0)
	{
		char* buffer = new char[size];
		memset(buffer, 0, size);
		fread(buffer, size, 1, hFile);
		//int status = luaL_loadbuffer(pState, (const char*)buffer, size, fullPath);
		int status = luaL_dostring(pState, buffer);
		if (status == LUA_OK)
		{

		}
	}
	else
	{
		std::string err = "\n\tError - MyLoader could not find ";
		err += module;
		err += ".";
		lua_pushstring(pState, err.c_str());
	}

	return 1;
}

void AddLoader(lua_State *L)
{
	int type = 0;
	lua_getglobal(L, "package");	// push "package"
	type = lua_type(L, -1);
	// lua_getfield(L, -1, "loaders");					// lua5.1 push "package.loaders"
	//lua_getfield(L, lua_upvalueindex(1), "searchers");					// lua5.3 push "package.searchers"
	lua_getfield(L, -1, "searchers");					// lua5.3 push "package.searchers"
	type = lua_type(L, -1);
	lua_remove(L, -2);								// remove "package"
	// Count the number of entries in package.loaders.
	// Table is now at index -2, since 'nil' is right on top of it.
	// lua_next pushes a key and a value onto the stack.
	int numLoaders = 0;
	lua_pushnil(L);
	while (lua_next(L, -2) != 0)
	{
		lua_pop(L, 1);
		numLoaders++;
	}

	lua_pushinteger(L, numLoaders + 1);
	lua_pushcfunction(L, MyLoader);
	lua_rawset(L, -3);
	// Table is still on the stack.  Get rid of it now.
	lua_pop(L, 1);
}
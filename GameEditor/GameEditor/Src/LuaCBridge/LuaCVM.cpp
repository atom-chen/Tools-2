#include "LuaCVM.h"
#include "LuaCObjectTranslator.h"
#include "LuaCObject.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCVM::LuaCVM()
{
	translator = new LuaCObjectTranslator;
	openLua();
}

LuaCVM::~LuaCVM()
{

}

void LuaCVM::openLua()
{
	/* initialize Lua */
	// L = lua_open();		// Lua5.1
	// L = lua_newstate();	// Lua5.3
	L = luaL_newstate();		// Lua5.3
	/* load Lua libraries */
	luaL_openlibs(L);
}

void LuaCVM::closeLua()
{
	lua_close(L);
}

LuaCObject* LuaCVM::getLuaObject(std::string fullPath)
{
	LuaCObject* returnValue = nullptr;
	int oldTop = lua_gettop(L);
	std::vector<std::string> path;
	std::string delim = ".";
	split(fullPath, delim, &path);

	lua_getglobal(L, path[0].c_str());
	returnValue = translator->getObject(L, -1);
	if (path.size() > 1)
	{
		std::vector<std::string> remainingPath;
		remainingPath.assign(path.begin() + 1, path.end());
		returnValue = getObject(remainingPath);
	}
	lua_settop(L, oldTop);
	return returnValue;
}

void LuaCVM::setLuaObject(std::string fullPath, LuaCObject* value)
{
	int oldTop = lua_gettop(L);
	std::vector<std::string> path;
	std::string delim = ".";
	split(fullPath, delim, &path);

	if (path.size() == 1)
	{
		translator->push(L, value);
		lua_setglobal(L, fullPath.c_str());
	}
	else
	{
		lua_getglobal(L, path[0].c_str());
		//lua_rawglobal(L, path[0]);			// lua_rawglobal 没有这个函数
		int type = lua_type(L, -1);

		if (type == LUA_TNIL)
		{
			// 输出日志
			lua_settop(L, oldTop);
			return;
		}

		std::vector<std::string> remainingPath;;
		remainingPath.assign(path.begin() + 1, path.end());
		setObject(remainingPath, value);
	}

	lua_settop(L, oldTop);
}

LuaCObject* LuaCVM::getObject(std::vector<std::string>& remainingPath)
{
	LuaCObject* returnValue = nullptr;
	for (int i = 0; i < remainingPath.size(); i++)
	{
		lua_pushstring(L, remainingPath[i].c_str());
		lua_gettable(L, -2);
		returnValue = translator->getObject(L, -1);
		if (returnValue == nullptr) break;
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

void LuaCVM::setObject(std::vector<std::string>& remainingPath, LuaCObject* val)
{
	for (int i = 0; i < remainingPath.size() - 1; i++)
	{
		lua_pushstring(L, remainingPath[i].c_str());
		lua_gettable(L, -2);
	}

	lua_pushstring(L, remainingPath[remainingPath.size() - 1].c_str());

	//可以释放先
	//if (val == null)
	//{
	//    LuaDLL.lua_gettable(L, -2);               
	//    LuaTypes type = LuaDLL.lua_type(L, -1);

	//    if (type == LuaTypes.LUA_TUSERDATA)
	//    {
	//        int udata = LuaDLL.luanet_tonetobject(L, -1);

	//        if (udata != -1)
	//        {
	//            translator.collectObject(udata);
	//        }
	//    }
	//}

	translator->push(L, val);
	lua_settable(L, -3);
}

END_NAMESPACE_GAMEEDITOR
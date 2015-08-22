#include "LuaCVM.h"
#include "LuaCObjectTranslator.h"
#include "LuaCObject.h"
#include "LuaCTable.h"
#include "LuaCommon.h"
#include "GameEditorSys.h"
#include "LuaCScriptMgr.h"

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

void LuaCVM::doString(std::string value)
{
	int ret = luaL_dostring(L, value.c_str());
	if (LUA_OK == ret)	// 执行成功
	{

	}
	else if (LUA_ERRRUN == ret)	// a runtime error. 
	{

	}
	else if (LUA_ERRMEM == ret)	// memory allocation error. For such errors, Lua does not call the error handler function. 
	{

	}
	else if (LUA_ERRERR == ret)	// error while running the error handler function. 
	{

	}
}

void LuaCVM::doFile(std::string path)
{
	luaL_dofile(L, path.c_str());
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
		lua_getglobal(L, path[0].c_str());		// lua5.3 lua_getglobal
		//lua_rawglobal(L, path[0]);			// lua5.1 lua_rawglobal
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

void LuaCVM::NewTable(std::string fullPath)
{
	std::vector<std::string> path;
	std::string delim = ".";
	split(fullPath, delim, &path);

	int oldTop = lua_gettop(L);
	if (path.size() == 1)
	{
		lua_newtable(L);
		lua_setglobal(L, fullPath.c_str());
	}
	else
	{
		lua_getglobal(L, path[0].c_str());
		for (int i = 1; i < path.size() - 1; i++)
		{
			lua_pushstring(L, path[i].c_str());
			lua_gettable(L, -2);
		}
		lua_pushstring(L, path[path.size() - 1].c_str());
		lua_newtable(L);
		lua_settable(L, -3);
	}
	lua_settop(L, oldTop);
}

LuaCTable* LuaCVM::NewTable()
{
	int oldTop = lua_gettop(L);

	lua_newtable(L);
	LuaCTable* returnVal = (LuaCTable*)translator->getObject(L, -1);

	lua_settop(L, oldTop);
	return returnVal;
}

LuaCObject* LuaCVM::rawGetObject(int reference, std::string field)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);
	lua_pushstring(L, field.c_str());
	lua_rawget(L, -2);
	LuaCObject* obj = translator->getObject(L, -1);
	lua_settop(L, oldTop);
	return obj;
}
/*
* Gets a field of the table or userdata corresponding to the provided reference
*/
LuaCObject* LuaCVM::getObject(int reference, std::string field)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);

	std::vector<std::string> path;
	std::string delim = ".";
	split(field, delim, &path);

	LuaCObject* returnValue = getObject(path);
	lua_settop(L, oldTop);
	return returnValue;
}
/*
* Gets a numeric field of the table or userdata corresponding the the provided reference
*/
LuaCObject* LuaCVM::getObject(int reference, LuaCObject* field)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);
	translator->push(L, field);
	lua_gettable(L, -2);
	LuaCObject* returnValue = translator->getObject(L, -1);
	lua_settop(L, oldTop);
	return returnValue;
}
/*
* Sets a field of the table or userdata corresponding the the provided reference
* to the provided value
*/
void LuaCVM::setObject(int reference, std::string field, LuaCObject* val)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);

	std::vector<std::string> path;
	std::string delim = ".";
	split(field, delim, &path);

	setObject(path, val);
	lua_settop(L, oldTop);
}
/*
* Sets a numeric field of the table or userdata corresponding the the provided reference
* to the provided value
*/
void LuaCVM::setObject(int reference, LuaCObject* field, LuaCObject* val)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);
	translator->push(L, field);
	translator->push(L, val);
	lua_settable(L, -3);
	lua_settop(L, oldTop);
}

// 注册一个函数
LuaCFunction* LuaCVM::RegisterFunction(std::string fullPath, lua_CFunction function)
{
	// We leave nothing on the stack when we are done
	int oldTop = lua_gettop(L);

	std::vector<std::string> path;
	std::string delim = ".";
	LuaCVM::split(fullPath, delim, &path);

	// 注册到表中
	if (path.size() > 1)
	{
		int dotIdx = fullPath.find_last_of(".");
		std::string tablePath = fullPath.substr(0, dotIdx);
		std::string lastPath = fullPath.substr(dotIdx + 1, fullPath.length() - (dotIdx + 1));
		LuaCTable* pLuaCTable = g_pLuaCScriptMgr->GetLuaTable(tablePath);
		pLuaCTable->setLuaFunction(lastPath, function);
	}
	else	// 注册到全局表中
	{
		lua_register(L, path[path.size() - 1].c_str(), function);	// 全局注册函数请使用这个
	}
	lua_settop(L, oldTop);

	LuaCFunction* f = g_pLuaCScriptMgr->GetLuaFunction(fullPath);
	return f;
}

//LuaCFunction LuaCVM::CreateFunction(LuaCObject* target, MethodBase function /*MethodInfo function*/)  //CP: Fix for struct constructor by Alexander Kappner (link: http://luaforge.net/forum/forum.php?thread_id=2859&forum_id=145)
//{
//	// We leave nothing on the stack when we are done
//	int oldTop = LuaDLL.lua_gettop(L);
//
//	LuaMethodWrapper wrapper = new LuaMethodWrapper(translator, target, function.DeclaringType, function);
//	translator.push(L, new LuaCSFunction(wrapper.call));
//
//	object obj = translator.getObject(L, -1);
//	LuaFunction f = (obj is LuaCSFunction ? new LuaFunction((LuaCSFunction)obj, this) : (LuaFunction)obj);
//
//	LuaDLL.lua_settop(L, oldTop);
//
//	return f;
//}

END_NAMESPACE_GAMEEDITOR
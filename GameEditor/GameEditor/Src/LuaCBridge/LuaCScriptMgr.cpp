#include "LuaCScriptMgr.h"
#include <sstream>
#include "LuaCVM.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCScriptMgr::LuaCScriptMgr()
{
	m_pLuaCVM = new LuaCVM;
	setLuaFilePath("D:/file/opensource/unity-game-git/unitygame/Tools/GameEditor/LuaScript");
	luaL_dofile(m_pLuaCVM->m_L, "TestLua.lua");
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	m_pLuaCVM->closeLua();
}

void LuaCScriptMgr::setLuaFilePath(std::string path)
{
	std::stringstream strStream;
	strStream << "local m_package_path = package.path" << "\r\n" << "package.path = string.format(\"%s;%s/?.lua\", m_package_path, " << path << ")";
	luaL_dostring(m_pLuaCVM->m_L, strStream.str().c_str());
}

void LuaCScriptMgr::setCFilePath(std::string path)
{

}

void LuaCScriptMgr::CheckArgsCount(lua_State* L, int count)
{
	int c = lua_gettop(L);

	if (c != count)
	{
		std::string str = "no overload for method '{0}' takes '{1}' arguments";
		luaL_error(L, str.c_str());
	}
}

//读取object类型，object为万用类型, 能读取所有从lua传递的参数
LuaCObject LuaCScriptMgr::GetVarObject(lua_State* L, int stackPos)
{
	LuaCObject ret;
	int type = lua_type(L, stackPos);

	switch (type)
	{
	case LUA_TNUMBER:
		ret.m_variant.m_float = lua_tonumber(L, stackPos);
	case LUA_TSTRING:
		ret.m_variant.m_pChar = lua_tostring(L, stackPos);
	case LUA_TUSERDATA:
	{
		ret.m_variant.m_pUserData = lua_touserdata(L, stackPos);

		//if (udata != -1)
		//{
		//	object obj = null;
		//	GetTranslator(L).objects.TryGetValue(udata, out obj);
		//	return obj;
		//}
		//else
		//{
		//	return null;
		//}
	}
	case LUA_TBOOLEAN:
		ret.m_variant.m_bool = lua_toboolean(L, stackPos);
	case LUA_TTABLE:
		return GetVarTable(L, stackPos);
	case LUA_TFUNCTION:
		lua_pushvalue(L, stackPos);
		return new LuaFunction(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
	default:
		return null;
	}

	return ret;
}

LuaCObject LuaCScriptMgr::GetVarTable(lua_State* L, int stackPos)
{
	LuaCObject o = null;
	int oldTop = lua_gettop(L);
	LuaDLL.lua_pushvalue(L, stackPos);
	LuaDLL.lua_pushstring(L, "class");
	LuaDLL.lua_gettable(L, -2);

	if (LuaDLL.lua_isnil(L, -1))
	{
		lua_settop(L, oldTop);
		lua_pushvalue(L, stackPos);
		o = new LuaCTable(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
	}
	else
	{
		string cls = LuaDLL.lua_tostring(L, -1);
		LuaDLL.lua_settop(L, oldTop);

		stackPos = stackPos > 0 ? stackPos : stackPos + oldTop + 1;

		if (cls == "Vector3")
		{
			o = GetVector3(L, stackPos);
		}
		else if (cls == "Vector2")
		{
			o = GetVector2(L, stackPos);
		}
		else if (cls == "Quaternion")
		{
			o = GetQuaternion(L, stackPos);
		}
		else if (cls == "Color")
		{
			o = GetColor(L, stackPos);
		}
		else if (cls == "Vector4")
		{
			o = GetVector4(L, stackPos);
		}
		else if (cls == "Ray")
		{
			o = GetRay(L, stackPos);
		}
		else if (cls == "Bounds")
		{
			o = GetBounds(L, stackPos);
		}
		else
		{
			LuaDLL.lua_pushvalue(L, stackPos);
			o = new LuaTable(LuaDLL.luaL_ref(L, LuaIndexes.LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
		}
	}

	//LuaDLL.lua_settop(L, oldTop);
	return o;
}

END_NAMESPACE_GAMEEDITOR
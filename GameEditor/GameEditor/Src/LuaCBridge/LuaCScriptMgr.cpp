#include "LuaCScriptMgr.h"
#include <sstream>
#include "LuaCVM.h"
#include "LuaCObjectTranslator.h"
#include <string>
#include "LuaCFunction.h"
#include "LuaCTable.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCObjectTranslator* LuaCScriptMgr::_translator = nullptr;

LuaCScriptMgr::LuaCScriptMgr()
{
	m_pLuaCVM = new LuaCVM;
	setLuaFilePath("D:/file/opensource/unity-game-git/unitygame/Tools/GameEditor/LuaScript");
	luaL_dofile(m_pLuaCVM->L, "TestLua.lua");
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	m_pLuaCVM->closeLua();
}

void LuaCScriptMgr::setLuaFilePath(std::string path)
{
	std::stringstream strStream;
	strStream << "local m_package_path = package.path" << "\r\n" << "package.path = string.format(\"%s;%s/?.lua\", m_package_path, " << path << ")";
	luaL_dostring(m_pLuaCVM->L, strStream.str().c_str());
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
LuaCObject* LuaCScriptMgr::GetVarObject(lua_State* L, int stackPos)
{
	LuaCObject* ret = nullptr;
	int type = lua_type(L, stackPos);

	switch (type)
	{
	case LUA_TNUMBER:
		ret->m_float = lua_tonumber(L, stackPos);
	case LUA_TSTRING:
		ret->m_pChar = lua_tostring(L, stackPos);
	case LUA_TUSERDATA:
	{
		ret->m_pUserData = lua_touserdata(L, stackPos);

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
		ret->m_bool = lua_toboolean(L, stackPos);
	case LUA_TTABLE:
		ret = GetVarTable(L, stackPos);
	case LUA_TFUNCTION:
		lua_pushvalue(L, stackPos);
		ret->m_pLuaCFunction = new LuaCFunction(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator(L)->interpreter);
	default:
		return nullptr;
	}

	return ret;
}

LuaCObject* LuaCScriptMgr::GetVarTable(lua_State* L, int stackPos)
{
	LuaCObject* o = nullptr;
	int oldTop = lua_gettop(L);
	lua_pushvalue(L, stackPos);
	lua_pushstring(L, "class");
	lua_gettable(L, -2);

	if (lua_isnil(L, -1))
	{
		lua_settop(L, oldTop);
		lua_pushvalue(L, stackPos);
		o->m_pLuaCTable = new LuaCTable(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator(L)->interpreter);
	}
	else
	{
		std::string cls = lua_tostring(L, -1);
		lua_settop(L, oldTop);

		stackPos = stackPos > 0 ? stackPos : stackPos + oldTop + 1;

		/*if (cls == "Vector3")
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
			lua_pushvalue(L, stackPos);
			o = new LuaTable(LuaDLL.luaL_ref(L, LuaIndexes.LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
		}*/
	}

	//LuaDLL.lua_settop(L, oldTop);
	return o;
}

LuaCObjectTranslator* LuaCScriptMgr::GetTranslator(lua_State* L)
{
#if MULTI_STATE
	return LuaCObjectTranslator.FromState(L);
#else            
	if (_translator == nullptr)
	{
		return LuaCObjectTranslator::FromState(L);
	}

	return _translator;
#endif        
}

//压入一个object变量
void LuaCScriptMgr::PushVarObject(lua_State* L, LuaCObject* o)
{
	if (o == nullptr)
	{
		lua_pushnil(L);
		return;
	}

	int t = o->GetType();

	//if (t.IsValueType)
	//{
	//	if (t == typeof(bool))
	//	{
	//		bool b = (bool)o;
	//		lua_pushboolean(L, b);
	//	}
	//	else if (t.IsEnum)
	//	{
	//		Push(L, (System.Enum)o);
	//	}
	//	else if (t.IsPrimitive)
	//	{
	//		double d = Convert.ToDouble(o);
	//		lua_pushnumber(L, d);
	//	}
	//	else if (t == typeof(Vector3))
	//	{
	//		Push(L, (Vector3)o);
	//	}
	//	else if (t == typeof(Vector2))
	//	{
	//		Push(L, (Vector2)o);
	//	}
	//	else if (t == typeof(Vector4))
	//	{
	//		Push(L, (Vector4)o);
	//	}
	//	else if (t == typeof(Quaternion))
	//	{
	//		Push(L, (Quaternion)o);
	//	}
	//	else if (t == typeof(Color))
	//	{
	//		Push(L, (Color)o);
	//	}
	//	else if (t == typeof(RaycastHit))
	//	{
	//		Push(L, (RaycastHit)o);
	//	}
	//	else if (t == typeof(Touch))
	//	{
	//		Push(L, (Touch)o);
	//	}
	//	else if (t == typeof(Ray))
	//	{
	//		Push(L, (Ray)o);
	//	}
	//	else
	//	{
	//		PushValue(L, o);
	//	}
	//}
	//else
	//{
	//	if (t.IsArray)
	//	{
	//		PushArray(L, (System.Array)o);
	//	}
	//	else if (t == typeof(LuaCSFunction))
	//	{
	//		GetTranslator(L).pushFunction(L, (LuaCSFunction)o);
	//	}
	//	else if (t.IsSubclassOf(typeof(Delegate)))
	//	{
	//		Push(L, (Delegate)o);
	//	}
	//	else if (IsClassOf(t, typeof(IEnumerator)))
	//	{
	//		Push(L, (IEnumerator)o);
	//	}
	//	else if (t == typeof(string))
	//	{
	//		string str = (string)o;
	//		LuaDLL.lua_pushstring(L, str);
	//	}
	//	else if (t == typeof(LuaStringBuffer))
	//	{
	//		LuaStringBuffer lsb = (LuaStringBuffer)o;
	//		LuaDLL.lua_pushlstring(L, lsb.buffer, lsb.buffer.Length);
	//	}
	//	else if (t.IsSubclassOf(typeof(UnityEngine.Object)))
	//	{
	//		UnityEngine.Object obj = (UnityEngine.Object)o;

	//		if (obj == null)
	//		{
	//			LuaDLL.lua_pushnil(L);
	//		}
	//		else
	//		{
	//			PushObject(L, o);
	//		}
	//	}
	//	else if (t == typeof(LuaTable))
	//	{
	//		((LuaTable)o).push(L);
	//	}
	//	else if (t == typeof(LuaFunction))
	//	{
	//		((LuaFunction)o).push(L);
	//	}
	//	else if (t == monoType)
	//	{
	//		Push(L, (Type)o);
	//	}
	//	else if (t.IsSubclassOf(typeof(TrackedReference)))
	//	{
	//		UnityEngine.TrackedReference obj = (UnityEngine.TrackedReference)o;

	//		if (obj == null)
	//		{
	//			LuaDLL.lua_pushnil(L);
	//		}
	//		else
	//		{
	//			PushObject(L, o);
	//		}
	//	}
	//	else
	//	{
	//		PushObject(L, o);
	//	}
	//}
}

END_NAMESPACE_GAMEEDITOR
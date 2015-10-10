#include "LuaCTable.h"
#include "LuaCVM.h"
#include "LuaCObject.h"
#include "LuaCommon.h"
#include "LuaCFunction.h"

LuaCTable::LuaCTable(int reference, LuaCVM* interpreter)
{
	m_ref = reference;
	m_luavm = interpreter;
}

LuaCTable::~LuaCTable()
{

}

LuaCObject* LuaCTable::getField(std::string field)
{
	return m_luavm->getObject(m_ref, field);
}

void LuaCTable::setField(std::string field, LuaCObject* value)
{
	m_luavm->setObject(m_ref, field, value);
}

//public System.Collections.IDictionaryEnumerator GetEnumerator()
//{
//return m_luavm.GetTableDict(this).GetEnumerator();
//}
//
//public int Count
//{
//get
//{
////push(m_luavm.L);
////LuaDLL.lua_objlen(m_luavm.L, -1);
//return m_luavm.GetTableDict(this).Count;
//}
//}
//
//public ICollection Keys
//{
//get{ return m_luavm.GetTableDict(this).Keys; }
//}
//
//public ICollection Values
//{
//get{ return m_luavm.GetTableDict(this).Values; }
//}

void LuaCTable::SetMetaTable(LuaCTable* metaTable)
{
	push(m_luavm->L);
	metaTable->push(m_luavm->L);
	lua_setmetatable(m_luavm->L, -2);
	lua_pop(m_luavm->L, 1);
}

//public T[] ToArray<T>()
//{
//	IntPtr L = m_luavm.L;
//	push(L);
//	return LuaScriptMgr.GetArrayObject<T>(L, -1);
//}

void LuaCTable::Set(std::string key, LuaCObject* o)
{
	lua_State* L = m_luavm->L;
	push(L);
	lua_pushstring(L, key.c_str());
	PushArgs(o);
	lua_rawset(L, -3);
	lua_settop(L, 0);
}

void LuaCTable::setLuaFunction(std::string key, lua_CFunction func)
{
	lua_State* L = m_luavm->L;
	push(L);
	lua_pushstring(L, key.c_str());
	lua_pushcfunction(L, func);
	lua_rawset(L, -3);
	lua_settop(L, 0);
}

/*
* Gets an string fields of a table ignoring its metatable,
* if it exists
*/
LuaCObject* LuaCTable::rawget(std::string field)
{
	return m_luavm->rawGetObject(m_ref, field);
}

LuaCObject* LuaCTable::rawgetFunction(std::string field)
{
	LuaCObject* obj = m_luavm->rawGetObject(m_ref, field);

	if (obj->GetType() == LUAC_TFUNCTION)
		//return new LuaCFunction((LuaCSFunction*)obj, m_luavm);
		return obj;
	else
		return obj;
}

LuaCFunction* LuaCTable::RawGetFunc(std::string field)
{
	lua_State* L = m_luavm->L;
	int type = LUA_TNONE;
	LuaCFunction* func = nullptr;

	int oldTop = lua_gettop(L);
	lua_getref(L, m_ref);
	lua_pushstring(L, field.c_str());
	lua_gettable(L, -2);

	type = lua_type(L, -1);

	if (type == LUA_TFUNCTION)
	{
		func = new LuaCFunction(luaL_ref(L, LUA_REGISTRYINDEX), L);
	}

	lua_settop(L, oldTop);
	return func;
}

/*
* Pushes this table into the Lua stack
// */
void LuaCTable::push(lua_State* luaState)
{
	lua_getref(luaState, m_ref);
}

std::string LuaCTable::ToString()
{
	return "table";
}
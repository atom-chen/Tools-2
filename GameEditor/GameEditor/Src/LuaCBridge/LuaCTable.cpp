#include "LuaCTable.h"
#include "LuaCVM.h"
#include "LuaCObject.h"
#include "LuaCommon.h"
#include "LuaCFunction.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCTable::LuaCTable(int reference, LuaCVM* interpreter)
{
	_Reference = reference;
	_Interpreter = interpreter;
	translator = interpreter->translator;
}

LuaCTable::~LuaCTable()
{

}

LuaCObject* LuaCTable::getField(std::string field)
{
	return _Interpreter->getObject(_Reference, field);
}

void LuaCTable::setField(std::string field, LuaCObject* value)
{
	_Interpreter->setObject(_Reference, field, value);
}

//public System.Collections.IDictionaryEnumerator GetEnumerator()
//{
//return _Interpreter.GetTableDict(this).GetEnumerator();
//}
//
//public int Count
//{
//get
//{
////push(_Interpreter.L);
////LuaDLL.lua_objlen(_Interpreter.L, -1);
//return _Interpreter.GetTableDict(this).Count;
//}
//}
//
//public ICollection Keys
//{
//get{ return _Interpreter.GetTableDict(this).Keys; }
//}
//
//public ICollection Values
//{
//get{ return _Interpreter.GetTableDict(this).Values; }
//}

void LuaCTable::SetMetaTable(LuaCTable* metaTable)
{
	push(_Interpreter->L);
	metaTable->push(_Interpreter->L);
	lua_setmetatable(_Interpreter->L, -2);
	lua_pop(_Interpreter->L, 1);
}

//public T[] ToArray<T>()
//{
//	IntPtr L = _Interpreter.L;
//	push(L);
//	return LuaScriptMgr.GetArrayObject<T>(L, -1);
//}

void LuaCTable::Set(std::string key, LuaCObject* o)
{
	lua_State* L = _Interpreter->L;
	push(L);
	lua_pushstring(L, key.c_str());
	PushArgs(L, o);
	lua_rawset(L, -3);
	lua_settop(L, 0);
}

void LuaCTable::setLuaFunction(std::string key, lua_CFunction func)
{
	lua_State* L = _Interpreter->L;
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
	return _Interpreter->rawGetObject(_Reference, field);
}

LuaCObject* LuaCTable::rawgetFunction(std::string field)
{
	LuaCObject* obj = _Interpreter->rawGetObject(_Reference, field);

	if (obj->GetType() == LUAC_TFUNCTION)
		//return new LuaCFunction((LuaCSFunction*)obj, _Interpreter);
		return obj;
	else
		return obj;
}

LuaCFunction* LuaCTable::RawGetFunc(std::string field)
{
	lua_State* L = _Interpreter->L;
	int type = LUA_TNONE;
	LuaCFunction* func = nullptr;

	int oldTop = lua_gettop(L);
	lua_getref(L, _Reference);
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
	lua_getref(luaState, _Reference);
}

std::string LuaCTable::ToString()
{
	return "table";
}

END_NAMESPACE_GAMEEDITOR
#include "LuaCObjectTranslator.h"
#include "LuaCObject.h"
#include "LuaCScriptMgr.h"

BEGIN_NAMESPACE_GAMEEDITOR

std::vector<LuaCObjectTranslator*> LuaCObjectTranslator::list;

LuaCObjectTranslator::LuaCObjectTranslator()
{

}

LuaCObjectTranslator::~LuaCObjectTranslator()
{

}

LuaCObject* LuaCObjectTranslator::getObject(lua_State* luaState, int index)
{
	return LuaCScriptMgr::GetVarObject(luaState, index);
}

LuaCObjectTranslator* LuaCObjectTranslator::FromState(lua_State* luaState)
{
	lua_getglobal(luaState, "_translator");
	int pos = (int)lua_tonumber(luaState, -1);
	lua_pop(luaState, 1);
	return list[pos];
}

void LuaCObjectTranslator::push(lua_State* luaState, LuaCObject* o)
{
	LuaCScriptMgr::PushVarObject(luaState, o);
}

END_NAMESPACE_GAMEEDITOR
#include "LuaCObjectTranslator.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCObjectTranslator::LuaCObjectTranslator()
{

}

LuaCObjectTranslator::~LuaCObjectTranslator()
{

}

LuaCObject getObject(lua_State luaState, int index)
{
	return LuaScriptMgr.GetVarObject(luaState, index);
}

END_NAMESPACE_GAMEEDITOR
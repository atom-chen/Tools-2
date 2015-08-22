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

std::vector<LuaCObject*> LuaCObjectTranslator::popValues(lua_State* luaState, int oldTop)
{
	std::vector<LuaCObject*> returnValues;

	int newTop = lua_gettop(luaState);

	if (oldTop == newTop)
	{
		return returnValues;
	}
	else
	{
		//std::vector<LuaCObject*> returnValues;

		for (int i = oldTop + 1; i <= newTop; i++)
		{
			returnValues.push_back(getObject(luaState, i));
		}

		lua_settop(luaState, oldTop);
		return returnValues;
	}
}

std::vector<LuaCObject*> LuaCObjectTranslator::popValues(lua_State* luaState, int oldTop, std::vector<int> popTypes)
{
	std::vector<LuaCObject*> returnValues;

	int newTop = lua_gettop(luaState);
	if (oldTop == newTop)
	{
		return returnValues;
	}
	else
	{
		int iTypes;
		//if (popTypes[0] == typeof(void))
		if (popTypes[0] == 0)
			iTypes = 1;
		else
			iTypes = 0;
		for (int i = oldTop + 1; i <= newTop; i++)
		{
			returnValues.push_back(getAsType(luaState, i, popTypes[iTypes]));
			iTypes++;
		}
		lua_settop(luaState, oldTop);
		return returnValues;
	}
}

LuaCObject* LuaCObjectTranslator::getAsType(lua_State* luaState, int stackPos, int paramType)
{
	return nullptr;
}

END_NAMESPACE_GAMEEDITOR
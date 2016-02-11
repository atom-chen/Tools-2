#include "LuaCObjectTranslator.h"
#include "LuaCObject.h"
#include "LuaCVM.h"

std::vector<LuaCObjectTranslator*> LuaCObjectTranslator::list;

LuaCObjectTranslator::LuaCObjectTranslator()
{

}

LuaCObjectTranslator::~LuaCObjectTranslator()
{

}

LuaCObject* LuaCObjectTranslator::getObject(int index)
{
	return interpreter->GetVarObject(index);
}

void LuaCObjectTranslator::push(LuaCObject* o)
{
	interpreter->PushVarObject(o);
}

std::vector<LuaCObject*> LuaCObjectTranslator::popValues(int oldTop)
{
	std::vector<LuaCObject*> returnValues;

	int newTop = lua_gettop(interpreter->L);

	if (oldTop == newTop)
	{
		return returnValues;
	}
	else
	{
		//std::vector<LuaCObject*> returnValues;

		for (int i = oldTop + 1; i <= newTop; i++)
		{
			returnValues.push_back(getObject(i));
		}

		lua_settop(interpreter->L, oldTop);
		return returnValues;
	}
}

std::vector<LuaCObject*> LuaCObjectTranslator::popValues(int oldTop, std::vector<int> popTypes)
{
	std::vector<LuaCObject*> returnValues;

	int newTop = lua_gettop(interpreter->L);
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
			returnValues.push_back(getAsType(i, popTypes[iTypes]));
			iTypes++;
		}
		lua_settop(interpreter->L, oldTop);
		return returnValues;
	}
}

LuaCObject* LuaCObjectTranslator::getAsType(int stackPos, int paramType)
{
	return nullptr;
}
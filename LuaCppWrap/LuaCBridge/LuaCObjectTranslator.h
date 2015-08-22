#ifndef __LuaCObjectTranslator_H_
#define __LuaCObjectTranslator_H_

#include "lua.hpp"
#include <vector>

class LuaCObject;
class LuaCVM;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class LuaCObjectTranslator
{
protected:
	static std::vector<LuaCObjectTranslator*> list;

public:
	LuaCVM* interpreter;

public:
	LuaCObjectTranslator();
	~LuaCObjectTranslator();
	LuaCObject* getObject(lua_State* luaState, int index);
	void push(lua_State* luaState, LuaCObject* o);
	std::vector<LuaCObject*> popValues(lua_State* luaState, int oldTop);
	std::vector<LuaCObject*> popValues(lua_State* luaState, int oldTop, std::vector<int> popTypes);
	LuaCObject* getAsType(lua_State* luaState, int stackPos, int paramType);

	static LuaCObjectTranslator* FromState(lua_State* luaState);
};

#endif
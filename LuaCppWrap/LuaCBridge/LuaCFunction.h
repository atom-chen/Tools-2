#ifndef __LuaCFunction_H_
#define __LuaCFunction_H_

#include "lua.hpp"
#include "LuaCBase.h"
#include <vector>

class LuaCVM;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class LuaCFunction : public LuaCBase
{
public:
	lua_State* L;

public:
	LuaCFunction(int reference, LuaCVM* interpreter);
	LuaCFunction(int reference, lua_State* l);
	~LuaCFunction();

	std::vector<LuaCObject*> LuaCFunction::call(std::vector<LuaCObject*> args, std::vector<int> returnTypes);
	std::vector<LuaCObject*> Call(std::vector<LuaCObject*> args);
	std::vector<LuaCObject*> LuaCFunction::Call();
	std::vector<LuaCObject*> LuaCFunction::Call(double arg1);
	int LuaCFunction::BeginPCall();
	bool LuaCFunction::PCall(int oldTop, int args);
	std::vector<LuaCObject*> LuaCFunction::PopValues(int oldTop);
	void LuaCFunction::EndPCall(int oldTop);
	lua_State* LuaCFunction::GetLuaState();
	void LuaCFunction::push(lua_State* luaState);
	void LuaCFunction::push();
	std::string LuaCFunction::ToString();
	int LuaCFunction::GetReference();
};

#endif
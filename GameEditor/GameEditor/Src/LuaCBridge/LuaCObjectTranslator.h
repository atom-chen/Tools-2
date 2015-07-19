#ifndef __LuaCObjectTranslator_H_
#define __LuaCObjectTranslator_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <vector>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCObject;
class LuaCVM;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class GAMEEDITOR_EXPORT LuaCObjectTranslator
{
protected:
#include "PushWarn.h"
	static std::vector<LuaCObjectTranslator*> list;
#include "PopWarn.h"

public:
	LuaCVM* interpreter;

public:
	LuaCObjectTranslator();
	~LuaCObjectTranslator();
	LuaCObject* getObject(lua_State* luaState, int index);
	void push(lua_State* luaState, LuaCObject* o);

	static LuaCObjectTranslator* FromState(lua_State* luaState);
};

END_NAMESPACE_GAMEEDITOR

#endif
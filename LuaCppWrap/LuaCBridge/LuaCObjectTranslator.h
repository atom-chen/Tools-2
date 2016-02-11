#ifndef __LuaCObjectTranslator_H_
#define __LuaCObjectTranslator_H_

#include "lua.hpp"
#include <vector>

class LuaCObject;
class LuaCVM;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h，从 lua 到 c 对象之间的转换
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
	LuaCObject* getObject(int index);
	void push(LuaCObject* o);
	std::vector<LuaCObject*> popValues(int oldTop);
	std::vector<LuaCObject*> popValues(int oldTop, std::vector<int> popTypes);
	LuaCObject* getAsType(int stackPos, int paramType);
};

#endif
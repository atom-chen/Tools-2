#ifndef __LuaCObjectTranslator_H_
#define __LuaCObjectTranslator_H_

#include "lua.hpp"
#include <vector>

class LuaCObject;
class LuaCVM;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h���� lua �� c ����֮���ת��
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
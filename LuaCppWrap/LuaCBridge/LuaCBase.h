#ifndef __LuaCBase_H_
#define __LuaCBase_H_

#include "lua.hpp"
#include <string>

class LuaCVM;
class LuaCObjectTranslator;
class LuaCObject;

class LuaCBase
{
public:
	bool _Disposed;
	int _Reference;
	LuaCVM* _Interpreter;

	std::string name;
	int count;

public:
	LuaCBase();
	~LuaCBase();

	void PushArgs(LuaCObject* o);
	int getRef();
	void AddRef();
};

#endif
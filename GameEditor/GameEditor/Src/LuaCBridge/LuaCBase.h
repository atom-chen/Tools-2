#ifndef __LuaCBase_H_
#define __LuaCBase_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;
class LuaCObjectTranslator;
class LuaCObject;

class GAMEEDITOR_EXPORT LuaCBase
{
public:
	bool _Disposed;
	int _Reference;
	LuaCVM* _Interpreter;
	LuaCObjectTranslator* translator;

#include "PushWarn.h"
	std::string name;
#include "PopWarn.h"
	int count;

public:
	LuaCBase();
	~LuaCBase();

	void PushArgs(lua_State* L, LuaCObject* o);
	int getRef();
	void AddRef();
};

END_NAMESPACE_GAMEEDITOR

#endif
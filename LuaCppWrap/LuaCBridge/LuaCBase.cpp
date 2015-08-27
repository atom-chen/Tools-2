#include "LuaCBase.h"
#include "LuaCScriptMgr.h"
#include "LuaCObject.h"

LuaCBase::LuaCBase()
{
	_Interpreter = nullptr;
	translator = nullptr;
	name = "";
	count = 1;
}

LuaCBase::~LuaCBase()
{
	//GC.SuppressFinalize(this);
}

void LuaCBase::PushArgs(lua_State* L, LuaCObject* o)
{
	LuaCScriptMgr::PushVarObject(L, o);
}

int LuaCBase::getRef()
{
	return _Reference;
}

void LuaCBase::AddRef()
{
	++count;
}
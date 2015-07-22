#include "LuaCBase.h"
#include "LuaCScriptMgr.h"
#include "LuaCObject.h"

BEGIN_NAMESPACE_GAMEEDITOR

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

END_NAMESPACE_GAMEEDITOR
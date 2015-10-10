#include "LuaCBase.h"
#include "LuaCScriptMgr.h"
#include "LuaCObject.h"
#include "LuaCVM.h"

LuaCBase::LuaCBase()
{
	_Interpreter = nullptr;
	name = "";
	count = 1;
}

LuaCBase::~LuaCBase()
{
	//GC.SuppressFinalize(this);
}

void LuaCBase::PushArgs(LuaCObject* o)
{
	_Interpreter->PushVarObject(o);
}

int LuaCBase::getRef()
{
	return _Reference;
}

void LuaCBase::AddRef()
{
	++count;
}
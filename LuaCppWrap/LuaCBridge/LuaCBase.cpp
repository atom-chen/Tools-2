#include "LuaCBase.h"
#include "LuaCScriptMgr.h"
#include "LuaCObject.h"
#include "LuaCVM.h"

LuaCBase::LuaCBase()
{
	m_luavm = nullptr;
	m_name = "";
	m_count = 1;
}

LuaCBase::~LuaCBase()
{
	//GC.SuppressFinalize(this);
}

void LuaCBase::PushArgs(LuaCObject* o)
{
	m_luavm->PushVarObject(o);
}

int LuaCBase::getRef()
{
	return m_ref;
}

void LuaCBase::AddRef()
{
	++m_count;
}
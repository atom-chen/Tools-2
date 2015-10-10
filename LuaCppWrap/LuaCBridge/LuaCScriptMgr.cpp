#include "LuaCScriptMgr.h"
#include "LuaCVM.h"

LuaCScriptMgr* LuaCScriptMgr::Instance = nullptr;

LuaCScriptMgr::LuaCScriptMgr()
{
	m_luavm = new LuaCVM();
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	m_luavm->closeLua();
}

LuaCVM* LuaCScriptMgr::getLuaCVM()
{
	return m_luavm;
}
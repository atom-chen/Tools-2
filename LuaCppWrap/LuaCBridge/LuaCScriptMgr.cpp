#include "LuaCScriptMgr.h"
#include "LuaCVM.h"

LuaCScriptMgr* LuaCScriptMgr::Instance = nullptr;

LuaCScriptMgr::LuaCScriptMgr()
{
	m_pLuaCVM = new LuaCVM();
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	m_pLuaCVM->closeLua();
}

LuaCVM* LuaCScriptMgr::getLuaCVM()
{
	return m_pLuaCVM;
}
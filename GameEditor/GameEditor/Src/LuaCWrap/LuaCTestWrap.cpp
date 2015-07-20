#include "LuaCTestWrap.h"
#include "GameEditorSys.h"
#include "LuaCScriptMgr.h"
#include "LuaCVM.h"
#include "LuaCTest.h"
#include "LuaCObject.h"

BEGIN_NAMESPACE_GAMEEDITOR

void LuaCTestWrap_Bind()
{
	lua_register(g_pLuaCScriptMgr->getLuaCVM()->L, "cHelloWorld", LuaCTestWrap_cHelloWorld);

	LuaCTest* pLuaCTest = new LuaCTest;
	LuaCObject* pLuaCObject = new LuaCObject;
	pLuaCObject->m_type = LUAC_TLIGHTUSERDATA;
	pLuaCObject->m_pLightUserData = pLuaCTest;
	g_pLuaCScriptMgr->getLuaCVM()->NewTable("aaa");
	g_pLuaCScriptMgr->getLuaCVM()->NewTable("aaa.bbb");
	g_pLuaCScriptMgr->getLuaCVM()->setLuaObject("aaa.bbb.ccc", pLuaCObject);

	lua_register(g_pLuaCScriptMgr->getLuaCVM()->L, "cppHelloHello", LuaCTestWrap_cppHelloHello);
}

int LuaCTestWrap_cHelloWorld(lua_State* L)
{
	LuaCScriptMgr::CheckArgsCount(L, 1);
	const char* pParam = lua_tostring(L, 1);
	//�˴���n��C++��ջ��ѹ��Ĳ��������������ѹ��ջ������һ�£����ܵ���ջʧ��
	return 0;
}

int LuaCTestWrap_cppHelloHello(lua_State* L)
{
	LuaCScriptMgr::CheckArgsCount(L, 2);
	LuaCTest* pLuaCTest = (LuaCTest*)lua_topointer(L, 1);
	const char* pParam = lua_tostring(L, 2);
	//�˴���n��C++��ջ��ѹ��Ĳ��������������ѹ��ջ������һ�£����ܵ���ջʧ��
	return 0;
}

END_NAMESPACE_GAMEEDITOR
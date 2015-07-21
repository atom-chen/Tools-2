#include "LuaCTestWrap.h"
#include "GameEditorSys.h"
#include "LuaCScriptMgr.h"
#include "LuaCVM.h"
#include "LuaCTest.h"
#include "LuaCObject.h"
#include "LuaCMember.h"

BEGIN_NAMESPACE_GAMEEDITOR

void LuaCTestWrap_Bind()
{
	testBind2f();
}

void testBind1f()
{
	lua_register(g_pLuaCScriptMgr->getLuaCVM()->L, "cHelloWorld", LuaCTestWrap_cHelloWorld);	// ȫ��ע�ắ����ʹ�����

	LuaCTest* pLuaCTest = new LuaCTest;
	pLuaCTest->setMem(10);
	LuaCObject* pLuaCObject = new LuaCObject;
	pLuaCObject->m_type = LUAC_TLIGHTUSERDATA;
	pLuaCObject->m_pLightUserData = pLuaCTest;
	//g_pLuaCScriptMgr->getLuaCVM()->NewTable("aaa");
	//g_pLuaCScriptMgr->getLuaCVM()->NewTable("aaa.bbb");
	//g_pLuaCScriptMgr->getLuaCVM()->setLuaObject("aaa.bbb.ccc", pLuaCObject);
	g_pLuaCScriptMgr->getLuaCVM()->setLuaObject("aaa", pLuaCObject);

	lua_register(g_pLuaCScriptMgr->getLuaCVM()->L, "cppHelloHello", LuaCTestWrap_cppHelloHello);
}

void testBind2f()
{
	std::vector<LuaMethod*> methodList;
	methodList.push_back(new LuaMethod("cHelloWorld", LuaCTestWrap_cHelloWorld));
	methodList.push_back(new LuaMethod("cppHelloHello", LuaCTestWrap_cppHelloHello));

	std::vector<LuaField*> fieldList;
	fieldList.push_back(new LuaField("log", nullptr, nullptr));

	//g_pLuaCScriptMgr->RegisterLib(g_pLuaCScriptMgr->getLuaCVM()->L, "SDK.Lib.TestStaticHandle", "LuaCTest", methodList, fieldList, "");
	g_pLuaCScriptMgr->RegisterLib(g_pLuaCScriptMgr->getLuaCVM()->L, "TestStaticHandle", "LuaCTest", methodList, fieldList, "");
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
	pLuaCTest->sayHello(pParam);
	//�˴���n��C++��ջ��ѹ��Ĳ��������������ѹ��ջ������һ�£����ܵ���ջʧ��
	return 0;
}

END_NAMESPACE_GAMEEDITOR
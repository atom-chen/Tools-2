#include "LuaCTestWrap.h"
#include "LuaCScriptMgr.h"
#include "LuaCVM.h"
#include "LuaCTest.h"
#include "LuaCObject.h"
#include "LuaCMember.h"
#include "lua.hpp"
#include "LuaCTable.h"

LuaCScriptMgr* g_pLuaCScriptMgr = new LuaCScriptMgr;

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

	lua_register(g_pLuaCScriptMgr->getLuaCVM()->L, "cppHelloHello", LuaCTestWrap_cppHelloWorld);
}

void testBind2f()
{
	std::vector<LuaMethod*> methodList;
	methodList.push_back(new LuaMethod("cHelloWorld", LuaCTestWrap_cHelloWorld));
	methodList.push_back(new LuaMethod("cppHelloHello", LuaCTestWrap_cppHelloWorld));

	std::vector<LuaField*> fieldList;
	fieldList.push_back(new LuaField("log", nullptr, nullptr));

	//g_pLuaCScriptMgr->RegisterLib(g_pLuaCScriptMgr->getLuaCVM()->L, "SDK.Lib.TestStaticHandle", "LuaCTest", methodList, fieldList, "");
	g_pLuaCScriptMgr->RegisterLib(g_pLuaCScriptMgr->getLuaCVM()->L, "TestStaticHandle", "LuaCTest", methodList, fieldList, "");

	const char* testfunc = "TestStaticHandle.cHelloWorld(\"ninhoa\")";
	g_pLuaCScriptMgr->doString(testfunc);
}

void testBind3f()
{
	LuaCTable* pTable = g_pLuaCScriptMgr->getLuaCVM()->NewTable();	// ����һ�����ŵ�ȫ�ֱ���
	LuaCObject* pObject = new LuaCObject;
	pObject->m_type = LUAC_TTABLE;
	pObject->m_pLuaCTable = pTable;
	g_pLuaCScriptMgr->getLuaCVM()->setLuaObject("hhh", pObject);

	pObject->m_type = LUAC_TFUNCTION;
	//pObject->m_pLuaCFunction = LuaCTestWrap_cHelloWorld;
	g_pLuaCScriptMgr->getLuaCVM()->setLuaObject("func", pObject);
}

void testBind4f()
{
	std::vector<LuaMethod*> methodList;
	methodList.push_back(new LuaMethod("cHelloWorld", LuaCTestWrap_cHelloWorld));
	methodList.push_back(new LuaMethod("cppHelloHello", LuaCTestWrap_cppHelloWorld));

	g_pLuaCScriptMgr->RegisterLib(g_pLuaCScriptMgr->getLuaCVM()->L, "asdf", methodList);
	LuaCTable* pTable = g_pLuaCScriptMgr->GetLuaTable("asdf");

	LuaCTest* pLuaCTest = new LuaCTest;
	LuaCObject* pObject = new LuaCObject;
	pObject->m_type = LUAC_TLIGHTUSERDATA;
	pObject->m_pLightUserData = pLuaCTest;

	pTable->setField("nihao", pObject);
}

void testBind5f()
{
	lua_register(g_pLuaCScriptMgr->getLuaCVM()->L, "cppHelloWorld", LuaCTestWrap_cppHelloWorld);	// ȫ��ע�ắ����ʹ�����
	LuaCTest* pLuaCTest = new LuaCTest;
	lua_pushlightuserdata(g_pLuaCScriptMgr->getLuaCVM()->L, pLuaCTest);
	lua_setglobal(g_pLuaCScriptMgr->getLuaCVM()->L, "asdf");

	const char* testCPPFunc = "asdf:cppHelloWorld(asdf, \"asasas\")";
	g_pLuaCScriptMgr->doString(testCPPFunc);
}

int LuaCTestWrap_cHelloWorld(lua_State* L)
{
	LuaCScriptMgr::CheckArgsCount(L, 1);
	const char* pParam = lua_tostring(L, 1);
	//�˴���n��C++��ջ��ѹ��Ĳ��������������ѹ��ջ������һ�£����ܵ���ջʧ��
	return 0;
}

int LuaCTestWrap_cppHelloWorld(lua_State* L)
{
	LuaCScriptMgr::CheckArgsCount(L, 2);
	LuaCTest* pLuaCTest = (LuaCTest*)lua_topointer(L, 1);
	pLuaCTest->setMem(123);
	const char* pParam = lua_tostring(L, 2);
	pLuaCTest->sayHello(pParam);
	//�˴���n��C++��ջ��ѹ��Ĳ��������������ѹ��ջ������һ�£����ܵ���ջʧ��
	return 0;
}
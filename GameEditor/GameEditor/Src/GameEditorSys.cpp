#include "GameEditorSys.h"
#include <assert.h>
#include "SkillActionNodeConfig.h"
#include "LuaCScriptMgr.h"
#include "LuaCTestWrap.h"

BEGIN_NAMESPACE_GAMEEDITOR

template <> GameEditorSys* Singleton<GameEditorSys>::ms_Singleton = 0;

GameEditorSys::GameEditorSys()
{
	m_pLuaCScriptMgr = new LuaCScriptMgr;
	m_pSkillActionNodeConfig = new SkillActionNodeConfig;
	LuaCTestWrap_Bind();
	//const char* testfunc = "cHelloWorld(\"ninhoa\")";
	//const char* testfunc = "LuaCTest.cHelloWorld(\"ninhoa\")";
	const char* testfunc = "TestStaticHandle.cHelloWorld(\"ninhoa\")";
	m_pLuaCScriptMgr->doString(testfunc);

	//const char* testCPPFunc = "aaa.bbb.ccc:cppHelloHello(\"ninhoa\")";
	const char* testCPPFunc = "cppHelloHello(aaa, \"ninhoa\")";
	m_pLuaCScriptMgr->doString(testCPPFunc);
}

void GameEditorSys::instanceT()
{
	assert(0);
	g_pGameEditorSys;
}

SkillActionNodeConfig* GameEditorSys::getSkillActionNodeConfigPtr()
{
	return m_pSkillActionNodeConfig;
}

LuaCScriptMgr* GameEditorSys::getLuaCScriptMgrPtr()
{
	return m_pLuaCScriptMgr;
}

void GameEditorSys::init()
{
	m_pSkillActionNodeConfig->loadXml();
}

END_NAMESPACE_GAMEEDITOR
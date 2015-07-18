#ifndef __AIEDITORSYS_H_
#define __AIEDITORSYS_H_

#include "GameEditor.h"

BEGIN_NAMESPACE_GAMEEDITOR

class SkillActionNodeConfig;
class LuaCScriptMgr;

class GAMEEDITOR_EXPORT GameEditorSys : public Singleton<GameEditorSys>
{
protected:
	SkillActionNodeConfig* m_pSkillActionNodeConfig;
	LuaCScriptMgr* m_pLuaCScriptMgr;

public:
	GameEditorSys();
	SkillActionNodeConfig* getSkillActionNodeConfigPtr();
	LuaCScriptMgr* getLuaCScriptMgrPtr();

	virtual void init();

private:
	// 不要手工调用这个函数，这个函数仅仅是为了当 AIEditor 模块没有使用 g_pGameEditorSys 的时候，导致模板类 Singleton 不能在 DLL 中导出的问题。如果 AIEditor 模块使用 g_pGameEditorSys，可以去掉这个函数。
	void instanceT();
};

#define g_pGameEditorSys GameEditorSys::getSingletonPtr()
#define g_pSkillActionNodeConfig g_pGameEditorSys->getSkillActionNodeConfigPtr()
#define g_pLuaCScriptMgr g_pGameEditorSys->getLuaCScriptMgrPtr()

END_NAMESPACE_GAMEEDITOR

#endif		// __AIEDITORSYS_H_
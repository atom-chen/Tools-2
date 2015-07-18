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
	// ��Ҫ�ֹ���������������������������Ϊ�˵� AIEditor ģ��û��ʹ�� g_pGameEditorSys ��ʱ�򣬵���ģ���� Singleton ������ DLL �е��������⡣��� AIEditor ģ��ʹ�� g_pGameEditorSys������ȥ�����������
	void instanceT();
};

#define g_pGameEditorSys GameEditorSys::getSingletonPtr()
#define g_pSkillActionNodeConfig g_pGameEditorSys->getSkillActionNodeConfigPtr()
#define g_pLuaCScriptMgr g_pGameEditorSys->getLuaCScriptMgrPtr()

END_NAMESPACE_GAMEEDITOR

#endif		// __AIEDITORSYS_H_
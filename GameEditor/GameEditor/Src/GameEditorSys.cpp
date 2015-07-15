#include "GameEditorSys.h"
#include <assert.h>
#include "SkillActionNodeConfig.h"

BEGIN_NAMESPACE_GAMEEDITOR

template <> GameEditorSys* Singleton<GameEditorSys>::ms_Singleton = 0;

GameEditorSys::GameEditorSys()
{
	m_pSkillActionNodeConfig = new SkillActionNodeConfig;
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

void GameEditorSys::init()
{
	m_pSkillActionNodeConfig->loadXml();
}

END_NAMESPACE_GAMEEDITOR
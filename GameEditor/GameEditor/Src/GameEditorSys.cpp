#include "GameEditorSys.h"
#include <assert.h>

BEGIN_NAMESPACE_GAMEEDITOR

template <> GameEditorSys* Singleton<GameEditorSys>::ms_Singleton = 0;

GameEditorSys::GameEditorSys()
{

}

void GameEditorSys::instanceT()
{
	assert(0);
	g_pGameEditorSys;
}

END_NAMESPACE_GAMEEDITOR
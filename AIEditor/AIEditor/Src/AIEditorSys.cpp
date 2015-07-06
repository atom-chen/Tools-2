#include "AIEditorSys.h"
#include <assert.h>

BEGIN_NAMESPACE_AIEDITOR

template <> AIEditorSys* Singleton<AIEditorSys>::ms_Singleton = 0;

AIEditorSys::AIEditorSys()
{

}

void AIEditorSys::instanceT()
{
	assert(0);
	g_pAIEditorSys;
}

END_NAMESPACE_AIEDITOR
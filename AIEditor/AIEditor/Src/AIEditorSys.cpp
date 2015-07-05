#include "AIEditorSys.h"

BEGIN_NAMESPACE_AIEDITOR

template <> AIEditorSys* Singleton<AIEditorSys>::ms_Singleton = 0;

AIEditorSys::AIEditorSys()
{

}

void AIEditorSys::instanceT()
{
	g_pAIEditorSys;
}

END_NAMESPACE_AIEDITOR
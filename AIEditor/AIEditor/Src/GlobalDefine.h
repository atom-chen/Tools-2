#ifndef __GlobalDefine_H_
#define __GlobalDefine_H_

//#define NO_NAMESPACE

#ifndef NO_NAMESPACE_GAMEEDITOR
	#define NSMESPACE_NAME_GAMEEDITOR GameEditor
	#define BEGIN_NAMESPACE_GAMEEDITOR namespace GameEditor {
	#define END_NAMESPACE_GAMEEDITOR }
	#define USING_NAMESPACE_GAMEEDITOR using namespace GameEditor;
#else
	#define NSMESPACE_NAME_GAMEEDITOR
	#define BEGIN_NAMESPACE_GAMEEDITOR
	#define END_NAMESPACE_GAMEEDITOR
	#define USING_NAMESPACE_GAMEEDITOR
#endif

#endif
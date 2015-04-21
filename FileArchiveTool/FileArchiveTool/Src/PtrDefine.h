#ifndef __PtrDefine_H_
#define __PtrDefine_H_

#include "GlobalDefine.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define SAFE_DELETE(ptr) \
	if(ptr != nullptr)\
	{\
		delete ptr;\
	}\
	else\
	{\
		FileArchiveToolSysDef->getLogSysPtr()->log("要删除的指针为空，不能正确删除");\
	}

END_NAMESPACE_FILEARCHIVETOOL

#endif
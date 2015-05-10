#ifndef __PtrDefine_H_
#define __PtrDefine_H_

#include "GlobalDefine.h"
#include "FileArchiveToolSys.h"
#include "LogSys.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define SAFE_DELETE(ptr) \
	if(ptr != nullptr)\
		{\
		delete ptr;\
		ptr = nullptr;\
	}\
	else\
	{\
		FileArchiveToolSysDef->getLogSysPtr()->log("要删除的指针为空，不能正确删除");\
	}

#define SAFE_DELETE_ARRAY(ptr) \
	if(ptr != nullptr)\
	{\
		delete[] ptr;\
		ptr = nullptr;\
	}\
	else\
	{\
		FileArchiveToolSysDef->getLogSysPtr()->log("要删除的指针数组为空，不能正确删除");\
	}

END_NAMESPACE_FILEARCHIVETOOL

#endif
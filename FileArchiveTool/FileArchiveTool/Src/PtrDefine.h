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
	}\
	else\
	{\
		FileArchiveToolSysDef->getLogSysPtr()->log("Ҫɾ����ָ��Ϊ�գ�������ȷɾ��");\
	}

#define SAFE_DELETE_ARRAY(ptr) \
	if(ptr != nullptr)\
	{\
		delete[] ptr;\
	}\
	else\
	{\
		FileArchiveToolSysDef->getLogSysPtr()->log("Ҫɾ����ָ������Ϊ�գ�������ȷɾ��");\
	}

END_NAMESPACE_FILEARCHIVETOOL

#endif
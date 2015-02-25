#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#include "GlobalDefine.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#if defined(WIN32)
	#if !defined(FILEARCHIVETOOL_DLL)
	#    define FILEARCHIVETOOL_EXPORT
	#else
	#    if defined( FILEARCHIVETOOL_DLL_EXPORT )
	#        define FILEARCHIVETOOL_EXPORT __declspec( dllexport )
	#    else
	#        define FILEARCHIVETOOL_EXPORT __declspec( dllimport )
	#    endif
	#endif
#endif

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef signed char int8;
// define uint64 type
#if defined(WIN32)
    typedef unsigned __int64 uint64;
    typedef __int64 int64;
#else
    typedef unsigned long long uint64;
    typedef long long int64;
#endif

// c:\Program Files(x86)\Windows Kits\8.1\Include\shared\minwindef.h		#define MAX_PATH          260
#ifdef MAX_PATH
#undef MAX_PATH
#endif
#define MAX_PATH 256			// 最大路径长度

END_NAMESPACE_FILEARCHIVETOOL

#endif
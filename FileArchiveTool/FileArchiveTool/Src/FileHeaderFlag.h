#ifndef __FileHeaderFlag_H
#define __FileHeaderFlag_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
*@brief 文件头标识，是对应的值
*/
enum FILEARCHIVETOOL_EXPORT FileHeaderFlagIndex
{
	eFHFI_CPS,		// 压缩位
};

/**
*@brief 文件头标识，是索引
*/
enum FILEARCHIVETOOL_EXPORT FileHeaderFlag
{
	eFHF_CPS = 1 << 0,		// 压缩位
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
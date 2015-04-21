#ifndef __PakParam_H
#define __PakParam_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

enum FILEARCHIVETOOL_EXPORT EPakParam
{
	ePP_Pak,			// 打包
	ePP_UnPak,			// 解包
};

class FILEARCHIVETOOL_EXPORT PakParam
{
protected:
	EPakParam m_ePakParam;

public:
	PakParam(EPakParam ePakParam);
	virtual ~PakParam();

	EPakParam getPakParamType();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
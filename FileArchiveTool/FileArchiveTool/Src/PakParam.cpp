#include "PakParam.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakParam::PakParam(EPakParam ePakParam)
{
	m_ePakParam = ePakParam;
}

PakParam::~PakParam()
{
	
}

EPakParam PakParam::getPakParamType()
{
	return m_ePakParam;
}

END_NAMESPACE_FILEARCHIVETOOL
#ifndef __WinLogDevice_H
#define __WinLogDevice_H

#include "LogDeviceBase.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT WinLogDevice : LogDeviceBase
{
public:
	WinLogDevice();
	~WinLogDevice();

	virtual void log(const char* msg);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
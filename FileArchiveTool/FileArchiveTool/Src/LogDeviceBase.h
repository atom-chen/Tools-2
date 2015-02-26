#ifndef __LogDeviceBase_H
#define __LogDeviceBase_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT LogDeviceBase
{
public:
	LogDeviceBase();
	virtual ~LogDeviceBase();

	virtual void log(const char* msg) = 0;
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
#ifndef __LogSys_H
#define __LogSys_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT LogSys
{
public:
	LogSys();
	~LogSys();

	void log(const char* msg);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
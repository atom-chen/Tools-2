#ifndef __ITask_H
#define __ITask_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT ITask
{
public:
	ITask();
	virtual ~ITask();
	virtual bool exeTask() = 0;
	virtual bool exeResult() = 0;
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
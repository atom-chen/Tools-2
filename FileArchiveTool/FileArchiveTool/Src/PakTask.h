#ifndef __PakTask_H
#define __PakTask_H

#include "ITask.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class PakItem;

class FILEARCHIVETOOL_EXPORT PakTask : public ITask
{
protected:
	PakItem* m_pPakItem;

public:
	PakTask(PakItem* pPakItem);
	~PakTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
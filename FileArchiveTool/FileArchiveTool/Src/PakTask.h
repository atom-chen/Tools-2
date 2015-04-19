#ifndef __PakTask_H
#define __PakTask_H

#include "ITask.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class PakItemBase;

class FILEARCHIVETOOL_EXPORT PakTask : public ITask
{
protected:
	PakItemBase* m_pPakItem;

public:
	PakTask(PakItemBase* pPakItem);
	~PakTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
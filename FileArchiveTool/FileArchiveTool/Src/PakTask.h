#ifndef __PakTask_H
#define __PakTask_H

#include "ITask.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class PakItemBase;
class ArchiveParam;
class UnArchiveParam;

class FILEARCHIVETOOL_EXPORT PakTask : public ITask
{
protected:
	PakItemBase* m_pPakItem;
	ArchiveParam* m_pArchiveParam;

public:
	PakTask(PakItemBase* pPakItem, ArchiveParam* pUnArchiveParam);
	~PakTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

class FILEARCHIVETOOL_EXPORT UnPakTask : public ITask
{
protected:
	PakItemBase* m_pPakItem;
	UnArchiveParam* m_pUnArchiveParam;

public:
	UnPakTask(PakItemBase* pPakItem, UnArchiveParam* pUnArchiveParam);
	~UnPakTask();

	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
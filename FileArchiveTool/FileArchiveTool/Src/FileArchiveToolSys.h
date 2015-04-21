#ifndef __FileArchiveToolSys_H_
#define __FileArchiveToolSys_H_

#include "Prerequisites.h"
#include "Singleton.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class Config;
class ArchiveData;
class CharsetConv;
class Util;
class TaskQueue;
class LogSys;
class ThreadPool;
class PakState;
class ManiFestData;

class FILEARCHIVETOOL_EXPORT FileArchiveToolSys : public Singleton<FileArchiveToolSys>
{
protected:
	Config* m_pConfig;		// ��������
	ArchiveData* m_pArchiveData;
	CharsetConv* m_pCharsetConv;
	Util* m_pUtil;
	TaskQueue* m_pTaskQueue;
	LogSys* m_pLogSys;
	ThreadPool* m_pThreadPool;
	PakState* m_pPakState;
	ManiFestData* m_pManiFestData;

public:
	FileArchiveToolSys();
	virtual ~FileArchiveToolSys();

public:
	virtual void onTick();
	virtual void init();	// ���캯�������������������
	virtual void destroy();	// �������ͷ�������Դ

	Config* getConfigPtr();
	ArchiveData* getArchiveDataPtr();
	CharsetConv* getCharsetConvPtr();
	Util* getUtilPtr();
	TaskQueue* getTaskQueuePtr();
	LogSys* getLogSysPtr();
	ThreadPool* getThreadPoolPtr();
	PakState* getPakStatePtr();
	ManiFestData* getManiFestDataPtr();
};

#define FileArchiveToolSysDef FileArchiveToolSys::getSingletonPtr()

END_NAMESPACE_FILEARCHIVETOOL

#endif
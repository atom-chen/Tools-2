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
//class ArchiveParam;
//class UnArchiveParam;
class ThreadPool;
class PakState;

class FILEARCHIVETOOL_EXPORT FileArchiveToolSys : public Singleton<FileArchiveToolSys>
{
protected:
	Config* m_pConfig;		// 基本配置
	ArchiveData* m_pArchiveData;
	CharsetConv* m_pCharsetConv;
	Util* m_pUtil;
	TaskQueue* m_pTaskQueue;
	LogSys* m_pLogSys;
	//ArchiveParam* m_pArchiveParam;
	//UnArchiveParam* m_pUnArchiveParam;
	ThreadPool* m_pThreadPool;
	PakState* m_pPakState;

public:
	FileArchiveToolSys();
	virtual ~FileArchiveToolSys();

public:
	virtual void onTick();
	virtual void init();	// 构造函数调用完成立马调用这个
	virtual void destroy();	// 最后调用释放所有资源

	Config* getConfigPtr();
	ArchiveData* getArchiveDataPtr();
	CharsetConv* getCharsetConvPtr();
	Util* getUtilPtr();
	TaskQueue* getTaskQueuePtr();
	LogSys* getLogSysPtr();
	//ArchiveParam* getArchiveParamPtr();
	//UnArchiveParam* getUnArchiveParamPtr();
	ThreadPool* getThreadPoolPtr();
	PakState* getPakStatePtr();
};

#define FileArchiveToolSysDef FileArchiveToolSys::getSingletonPtr()

END_NAMESPACE_FILEARCHIVETOOL

#endif
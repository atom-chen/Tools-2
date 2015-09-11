#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H

#include <QtCore/QtCore>

#include "Platform.h"

QT_FORWARD_DECLARE_CLASS(QThread);

BEGIN_NAMESPACE

class WorkThread : public QThread
{
protected:
	bool m_running;

public:
	WorkThread();
	~WorkThread();
	bool isRunning();
	void startThread();
	virtual void run();
};

class ExcelWorkThread : public WorkThread
{
public:
	virtual void run();
};

class CodeWorkThread : public WorkThread
{
protected:
	bool m_bCppCode;
	bool m_bCsCode;

public:
	CodeWorkThread();
	bool getCppCode();
	void setCppCode(bool bCppCode);
	bool getCsCode();
	void setCsCode(bool bCsCode);
	virtual void run();
};

END_NAMESPACE

#endif
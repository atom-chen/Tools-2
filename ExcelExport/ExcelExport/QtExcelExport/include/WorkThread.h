#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H

#include <QtCore/QtCore>

//class ExcelTbl;

#include "Platform.h"

QT_FORWARD_DECLARE_CLASS(QThread);

BEGIN_NAMESPACE

class WorkThread : public QThread
{
private:
	//ExcelTbl* m_excelTbl;

public:
	//void setParam(ExcelTbl* para);
	virtual void run();
};

END_NAMESPACE

#endif	// WORKTHREAD_H  
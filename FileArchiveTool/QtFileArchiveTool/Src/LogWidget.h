#ifndef __LOGWIDGET_H
#define __LOGWIDGET_H

#include <QtWidgets>
#include "FileArchiveTool.h"

namespace Ui
{
	class LogWidget;
}

class LogWidget : public QDockWidget, public LogDeviceBase
{
	Q_OBJECT

public:
	explicit LogWidget(QWidget *parent = 0);
	~LogWidget();

public:
	virtual void log(const char* msg);

private:
	Ui::LogWidget *m_ui;
};

#endif // LOGWIDGET_H
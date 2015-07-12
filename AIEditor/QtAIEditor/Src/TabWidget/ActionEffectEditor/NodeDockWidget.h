#ifndef __NodeDockWidget_H
#define __NodeDockWidget_H

#include "MyTabSubWidgetBase.h"
#include "QtIncAll.h"

class NodeDockWidget : public QDockWidget
{
	Q_OBJECT

protected:
	QVBoxLayout * m_pHbox;
	QScrollArea* m_pQScrollArea;

public:
	NodeDockWidget(QWidget *parent = 0);
	~NodeDockWidget();
};

#endif
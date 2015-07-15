#ifndef __NodeDockWidget_H
#define __NodeDockWidget_H

#include "MyTabSubWidgetBase.h"
#include "QtIncAll.h"

class MyScrollAreaWidget;

class NodeDockWidget : public QDockWidget
{
	Q_OBJECT

protected:
	QGridLayout * m_pHbox;
	MyScrollAreaWidget* m_pScrollArea;
	//qdesigner_internal::QDesignerWidgetBox* m_pDesignerWidgetBox;

public:
	NodeDockWidget(QWidget *parent = 0);
	~NodeDockWidget();
};

#endif
#ifndef __MyTabSubWidgetBase_H
#define __MyTabSubWidgetBase_H

#include <QMainWindow>
#include "TabSubWidgetLogicData.h"

class MyTabSubWidgetBase : public QMainWindow, public TabSubWidgetLogicData
{
	Q_OBJECT
public:
	MyTabSubWidgetBase(QWidget* = 0);
	~MyTabSubWidgetBase();
};

#endif
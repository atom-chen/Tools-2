#ifndef __MyTabSubWidgetBase_H
#define __MyTabSubWidgetBase_H

#include <QWidget>
#include "TabSubWidgetLogicData.h"

class MyTabSubWidgetBase : public QWidget, public TabSubWidgetLogicData
{
	Q_OBJECT
public:
	MyTabSubWidgetBase(QWidget* = 0);
	~MyTabSubWidgetBase();
};

#endif
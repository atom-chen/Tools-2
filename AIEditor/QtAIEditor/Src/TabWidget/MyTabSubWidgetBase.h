#ifndef __MyTabSubWidgetBase_H
#define __MyTabSubWidgetBase_H

#include <QWidget>

class MyTabSubWidgetBase : public QWidget
{
	Q_OBJECT
public:
	MyTabSubWidgetBase(QWidget* = 0);
	~MyTabSubWidgetBase();
};

#endif
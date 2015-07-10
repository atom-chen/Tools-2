#ifndef __MyTabSubWidgetFrame_H
#define __MyTabSubWidgetFrame_H

#include <QWidget>

class MyTabSubWidgetFrame :public QWidget
{
	Q_OBJECT
public:
	MyTabSubWidgetFrame(QWidget* = 0);
	~MyTabSubWidgetFrame();
protected:
	bool event(QEvent *);
signals:
	void sig_doubleClickedTitleBar();  //被双击时发射的信号
};

#endif
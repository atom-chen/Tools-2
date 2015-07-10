#ifndef __MyTabSubWidget_H
#define __MyTabSubWidget_H

#include <QWidget>

class MyTabSubWidget :public QWidget
{
	Q_OBJECT
public:
	MyTabSubWidget(QWidget* = 0);
	~MyTabSubWidget();
protected:
	bool event(QEvent *);
signals:
	void sig_doubleClickedTitleBar();  //被双击时发射的信号
};
#endif
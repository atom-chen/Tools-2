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
	void sig_doubleClickedTitleBar();  //��˫��ʱ������ź�
};
#endif
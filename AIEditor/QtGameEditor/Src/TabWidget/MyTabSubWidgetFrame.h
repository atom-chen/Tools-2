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
	void sig_doubleClickedTitleBar();  //��˫��ʱ������ź�
};

#endif
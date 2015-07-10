#ifndef __MyTabBar_H
#define __MyTabBar_H
#include <QTabBar>
#include <QtGui>

class MyTabBar :public QTabBar
{
	Q_OBJECT
public:
	MyTabBar(QWidget* = 0);
	virtual ~MyTabBar(){};
protected:
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);   //通过两个事件模拟出tab被拖动的动作
private:
	bool pressFlag;
signals:
	void sig_tabDrag(int, QPoint);
};
#endif
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
	void mouseReleaseEvent(QMouseEvent *);   //ͨ�������¼�ģ���tab���϶��Ķ���
private:
	bool pressFlag;
signals:
	void sig_tabDrag(int, QPoint);
};
#endif
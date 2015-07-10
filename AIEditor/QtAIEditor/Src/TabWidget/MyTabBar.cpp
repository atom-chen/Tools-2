#include "MyTabBar.h"
#include <QtGui>

MyTabBar::MyTabBar(QWidget *parent) :QTabBar(parent), pressFlag(false)
{

}

void MyTabBar::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		pressFlag = true;
	}
	QTabBar::mousePressEvent(event);
}

void MyTabBar::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton &&pressFlag)
	{
		pressFlag = false;
		if (tabRect(currentIndex()).contains(event->pos()))
			return;
		emit sig_tabDrag(currentIndex(), event->pos());
	}
}
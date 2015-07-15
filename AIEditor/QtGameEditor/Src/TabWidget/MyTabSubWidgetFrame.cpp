#include "MyTabSubWidgetFrame.h"
#include <QtGui>

MyTabSubWidgetFrame::MyTabSubWidgetFrame(QWidget *parent) :QWidget(parent)
{

}

MyTabSubWidgetFrame::~MyTabSubWidgetFrame()
{

}

bool MyTabSubWidgetFrame::event(QEvent *event)
{
#ifdef unix
	if (event->type() == QEvent::MouseButtonDblClick){   //����������û��Ӧ���͵������ڱ�Ե�����
		emit sig_doubleClickedTitleBar();
		return true;
	}
#endif   
	if (event->type() == QEvent::NonClientAreaMouseButtonDblClick)  //����¼���Linux��û�д�����Ӧ������Qt��һ��Bug��
	{
		emit sig_doubleClickedTitleBar();
		return true;
	}
	return QWidget::event(event);
}
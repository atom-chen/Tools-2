#ifndef __GRAPHICSVIEW_H
#define __GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

//protected:
//	QPointF m_lastPos;

public:
	explicit GraphicsView(QWidget *parent = 0);
	void adjustSceneRect();	// ���� VIEW ʼ�������ܷ�����������������

protected:
	virtual void paintEvent(QPaintEvent *e);
	// ������¼�һ��Ҫ���� Parent ����������Ͳ����Զ��ƶ���
	virtual void mouseMoveEvent(QMouseEvent * e);//����ƶ��¼���Ӧ
	virtual void mousePressEvent(QMouseEvent * e);//��굥���¼���Ӧ
	virtual void mouseReleaseEvent(QMouseEvent * e);//����ɿ��¼���Ӧ
	virtual void GraphicsView::dragEnterEvent(QDragEnterEvent *event);
	virtual void GraphicsView::dropEvent(QDropEvent *event);
};

#endif // GRAPHICSVIEW_H
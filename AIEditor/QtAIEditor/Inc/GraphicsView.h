#ifndef __GRAPHICSVIEW_H
#define __GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
	explicit GraphicsView(QWidget *parent = 0);

protected:
	//void paintEvent(QPaintEvent *e);
	// ������¼��Ͳ����Զ��ƶ���
	//void mouseMoveEvent(QMouseEvent * e);//����ƶ��¼���Ӧ
	//void mousePressEvent(QMouseEvent * e);//��굥���¼���Ӧ
	//void mouseReleaseEvent(QMouseEvent * e);//����ɿ��¼���Ӧ
};

#endif // GRAPHICSVIEW_H
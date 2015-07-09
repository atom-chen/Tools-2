#ifndef __DRAGWIDGET_H
#define __DRAGWIDGET_H

#include <QWidget>
#include <QGraphicsItem>

class QHBoxLayout;
class GraphicsView;
class GraphicsScene;

class DragWidget : public QWidget
{
    Q_OBJECT

protected:
	QHBoxLayout * m_pHbox;
	GraphicsView * m_pView;
	GraphicsScene * m_pScene;

public:
	DragWidget(QWidget *parent = 0);
    void makeDraggable(QGraphicsItem *);
	~DragWidget();

protected:
	void addMultiPolygon();
	void addEllipse();
	void addDragWidget();
	void addBezierCurve();
};

#endif // __DRAGWIDGET_H
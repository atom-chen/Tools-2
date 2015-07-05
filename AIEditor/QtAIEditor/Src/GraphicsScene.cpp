#include "GraphicsScene.h"
#include <QDebug>
#include "QtAIEditorSys.h"
#include "DragDropSys.h"
#include "BezierCurveItem.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}


void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * m)
{
//    qDebug() << //Q_FUNC_INFO <<
//                m->scenePos();
//    m->ignore();
    QGraphicsScene::mouseMoveEvent(m);

	if (g_pDragDropSys->getStartDrag())
	{
		QPointF coursePoint;
		coursePoint = m->pos();//获取当前光标的位置
		QPoint intPt;
		g_pDragDropSys->getBezierCurveItem()->setEndPos(&intPt);
		g_pDragDropSys->getBezierCurveItem()->updateCtrlPos();
	}
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *evt)
{
	QGraphicsScene::mousePressEvent(evt);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *evt)
{
	QGraphicsScene::mouseReleaseEvent(evt);
}

void GraphicsScene::addGraphicsObject(QGraphicsObject* pQGraphicsObject)
{
	addItem(pQGraphicsObject);
}
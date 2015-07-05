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
		//coursePoint = m->pos();//获取当前光标的位置，这个值总是为 0
		coursePoint = m->scenePos();
		//coursePoint = m->screenPos();
		QPoint intPt;
		intPt.setX(coursePoint.x());
		intPt.setY(coursePoint.y());
		g_pDragDropSys->getBezierCurveItem()->setEndPos(&intPt);
		g_pDragDropSys->getBezierCurveItem()->updateCtrlPos();
	}

	if (this->m_lastPos != m->scenePos())
	{
		this->m_lastPos = m->scenePos();
		QTransform transform;
		transform.rotate(0);
		transform.scale(1, 1);
		transform.translate(0, 0);
		QGraphicsItem *item = this->itemAt(this->m_lastPos, transform);		// 最新的接口需要 QTransform 参数
		if (item)
		{
			QGraphicsItem* pathItem = (QGraphicsItem*)item;
			QPointF pathItemPos = pathItem->mapFromScene(m->scenePos());
			// 这里是橡皮擦擦除函数,我已经在代码中注释掉了。避免因为算法原因导致程序很卡
			// pathItem->pixEarsePath(pathItemPos , this->m_pix_earse_size);
		}
		QRect rect;
		rect.setTopLeft(this->m_lastPos.toPoint() - QPoint(500, 500));
		rect.setBottomRight(this->m_lastPos.toPoint() + QPoint(500, 500));
		//这里就是刷新函数，用来刷新scene，但是它同时也会自动刷新item
		this->invalidate(rect, QGraphicsScene::AllLayers);	// 重新绘制窗口区域，如果不重新绘制
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
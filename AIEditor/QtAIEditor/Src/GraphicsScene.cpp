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
		//coursePoint = m->pos();//��ȡ��ǰ����λ�ã����ֵ����Ϊ 0
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
		QGraphicsItem *item = this->itemAt(this->m_lastPos, transform);		// ���µĽӿ���Ҫ QTransform ����
		if (item)
		{
			QGraphicsItem* pathItem = (QGraphicsItem*)item;
			QPointF pathItemPos = pathItem->mapFromScene(m->scenePos());
			// ��������Ƥ����������,���Ѿ��ڴ�����ע�͵��ˡ�������Ϊ�㷨ԭ���³���ܿ�
			// pathItem->pixEarsePath(pathItemPos , this->m_pix_earse_size);
		}
		QRect rect;
		rect.setTopLeft(this->m_lastPos.toPoint() - QPoint(500, 500));
		rect.setBottomRight(this->m_lastPos.toPoint() + QPoint(500, 500));
		//�������ˢ�º���������ˢ��scene��������ͬʱҲ���Զ�ˢ��item
		this->invalidate(rect, QGraphicsScene::AllLayers);	// ���»��ƴ���������������»���
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
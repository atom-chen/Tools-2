#include "GraphicsView.h"
#include "QtAIEditorSys.h"
#include "DragDropSys.h"
#include "GraphicsScene.h"
#include "BezierCurveItem.h"

GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
}

void GraphicsView::paintEvent(QPaintEvent *e)
{
	QGraphicsView::paintEvent(e);

//	QPainter painter(this);
//	painter.setRenderHint(QPainter::Antialiasing, true);
//	QPen pen;
//	pen.setColor(Qt::red);
//	pen.setWidth(2);
//	pen.setStyle(Qt::DashDotLine);
//	painter.setPen(pen);
//
//	//define startpos endpos
//	QPoint start_pos(300, 50);
//	QPoint end_pos(100, 200);
//
//	//drawPath;
//	QPainterPath path(start_pos);
//	QPoint c1((start_pos + end_pos).x() / 2, start_pos.y());
//	QPoint c2((start_pos + end_pos).x() / 2, end_pos.y());
//
//	path.cubicTo(c1, c2, end_pos);
//	painter.drawPath(path);
//	//
//	QPen penshaper;
//	penshaper.setStyle(Qt::SolidLine);
//	penshaper.setColor(Qt::darkRed);
//	painter.setPen(penshaper);
//
//	//#define the rect size;
//	QSize rect_size(60, 60);
//	QRect rect_shape1(start_pos - QPoint(rect_size.height() / 2, rect_size.width() / 2), rect_size);
//	QRect rect_shape2(end_pos - QPoint(rect_size.height() / 2, rect_size.width() / 2), rect_size);
//
//	QBrush brush(Qt::darkGray, Qt::CrossPattern);
//	painter.fillRect(rect_shape1, brush);
//	painter.fillRect(rect_shape2, brush);
//	painter.drawRoundedRect(rect_shape1, 10, 10);
//	painter.drawRoundedRect(rect_shape2, 10, 10);
//
//	QPen dotpen;
//	dotpen.setWidth(8);
//	dotpen.setColor(Qt::red);
//
//	brush.setStyle(Qt::SolidPattern);
//	painter.setPen(dotpen);
//	painter.drawPoint(start_pos);
//	painter.drawPoint(end_pos);
}

void GraphicsView::mouseMoveEvent(QMouseEvent * e)//鼠标移动事件响应
{
	QGraphicsView::mouseMoveEvent(e);

	QPoint cursePoint;
	cursePoint = e->pos();								//获取当前光标的位置
	QPointF scenePos = this->mapToScene(cursePoint);	// 转换成场景位置

	//if (g_pDragDropSys->getStartDrag())
	//{
	//	QPoint intPt;
	//	intPt.setX(scenePos.x());
	//	intPt.setY(scenePos.y());
	//	g_pDragDropSys->getBezierCurveItem()->setEndPos(&intPt);
	//	g_pDragDropSys->getBezierCurveItem()->updateCtrlPos();
	//}

	//if (this->m_lastPos != scenePos)
	//{
	//	this->m_lastPos = scenePos;
	//	QTransform transform;
	//	transform.rotate(0);
	//	transform.scale(1, 1);
	//	transform.translate(0, 0);
	//	QGraphicsItem *item = this->scene()->itemAt(this->m_lastPos, transform);		// 最新的接口需要 QTransform 参数
	//	if (item)
	//	{
	//		QGraphicsItem* pathItem = (QGraphicsItem*)item;
	//		QPointF pathItemPos = pathItem->mapFromScene(scenePos);
	//		// 这里是橡皮擦擦除函数,我已经在代码中注释掉了。避免因为算法原因导致程序很卡
	//		// pathItem->pixEarsePath(pathItemPos , this->m_pix_earse_size);
	//	}
	//	QRect rect;
	//	rect.setTopLeft(this->m_lastPos.toPoint() - QPoint(500, 500));
	//	rect.setBottomRight(this->m_lastPos.toPoint() + QPoint(500, 500));
	//	//这里就是刷新函数，用来刷新scene，但是它同时也会自动刷新item
	//	this->invalidateScene(rect, QGraphicsScene::AllLayers);	// 重新绘制窗口区域，如果不重新绘制，可能有些就会显示错误
	//}
}

void GraphicsView::mousePressEvent(QMouseEvent * e)//鼠标单击事件响应
{
	QGraphicsView::mousePressEvent(e);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent * e)//鼠标松开事件响应
{
	QGraphicsView::mouseReleaseEvent(e);
	adjustSceneRect();
}

void GraphicsView::adjustSceneRect()
{
	this->setSceneRect(g_pGraphicsScene->itemsBoundingRect());
}
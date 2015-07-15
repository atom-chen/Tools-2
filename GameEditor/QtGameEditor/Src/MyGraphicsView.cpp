#include "MyGraphicsView.h"
#include "QtGameEditorSys.h"
#include "DragDropSys.h"
#include "MyGraphicsScene.h"
#include "BezierCurveItem.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setRenderHint(QPainter::Antialiasing);
	this->setMouseTracking(true);
	//this->setDragMode(ScrollHandDrag);	// �ϷŻ����֡�QGraphicsView �ǲ��ܽ�����ק�ģ������϶��� QGraphicsItem �ϲ���
	this->setAcceptDrops(true);		// �����϶�����
}

void MyGraphicsView::paintEvent(QPaintEvent *e)
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

void MyGraphicsView::mouseMoveEvent(QMouseEvent * e)//����ƶ��¼���Ӧ
{
	QGraphicsView::mouseMoveEvent(e);

	QPoint cursePoint;
	cursePoint = e->pos();								//��ȡ��ǰ����λ��
	QPointF scenePos = this->mapToScene(cursePoint);	// ת���ɳ���λ��

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
	//	QGraphicsItem *item = this->scene()->itemAt(this->m_lastPos, transform);		// ���µĽӿ���Ҫ QTransform ����
	//	if (item)
	//	{
	//		QGraphicsItem* pathItem = (QGraphicsItem*)item;
	//		QPointF pathItemPos = pathItem->mapFromScene(scenePos);
	//		// ��������Ƥ����������,���Ѿ��ڴ�����ע�͵��ˡ�������Ϊ�㷨ԭ���³���ܿ�
	//		// pathItem->pixEarsePath(pathItemPos , this->m_pix_earse_size);
	//	}
	//	QRect rect;
	//	rect.setTopLeft(this->m_lastPos.toPoint() - QPoint(500, 500));
	//	rect.setBottomRight(this->m_lastPos.toPoint() + QPoint(500, 500));
	//	//�������ˢ�º���������ˢ��scene��������ͬʱҲ���Զ�ˢ��item
	//	this->invalidateScene(rect, QGraphicsScene::AllLayers);	// ���»��ƴ���������������»��ƣ�������Щ�ͻ���ʾ����
	//}
}

void MyGraphicsView::mousePressEvent(QMouseEvent * e)//��굥���¼���Ӧ
{
	QGraphicsView::mousePressEvent(e);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent * e)//����ɿ��¼���Ӧ
{
	QGraphicsView::mouseReleaseEvent(e);
	onSceneResize();
}

void MyGraphicsView::onSceneResize()
{
	this->setSceneRect(g_pGraphicsScene->itemsBoundingRect());
}

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/plain"))
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
		//event->acceptProposedAction();
	}

	//QGraphicsView::dragEnterEvent(event);
}

void MyGraphicsView::dropEvent(QDropEvent *event)
{
	//textBrowser->setPlainText(event->mimeData()->text());
	//mimeTypeCombo->clear();
	//mimeTypeCombo->addItems(event->mimeData()->formats());
	event->acceptProposedAction();

	QGraphicsView::dropEvent(event);
}

void MyGraphicsView::resizeEvent(QResizeEvent *evt)
{
	// View �����������򶼿����Ϸ�
	QPoint viewLeftTopPos = QPoint(0, 0);
	QPointF sceneLeftTopPos = this->mapToScene(viewLeftTopPos);	// ת���ɳ���λ��
	QPoint viewRightBtmPos = QPoint(this->size().width(), this->size().height());
	QPointF sceneRightBtmPos = this->mapToScene(viewRightBtmPos);

	g_pGraphicsScene->adjustSceneRect(sceneLeftTopPos, sceneRightBtmPos);
}
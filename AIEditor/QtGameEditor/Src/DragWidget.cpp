#include "DragWidget.h"
#include <QGraphicsView>
#include "Mygraphicsscene.h"
#include <QHBoxLayout>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <qmath.h>
#include "BoardHexagon.h"
#include "DraggableItemBase.h"
#include "MyGraphicsView.h"
#include "BezierCurveItem.h"
#include "QtGameEditorSys.h"

DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent)
{
	m_pHbox = new QHBoxLayout;
    //QGraphicsView * view = new QGraphicsView;
	m_pView = new MyGraphicsView;
	m_pScene = new MyGraphicsScene;

	addMultiPolygon();
	addEllipse();
	addDragWidget();
	addBezierCurve();

	m_pView->setRenderHint(QPainter::Antialiasing);
	m_pView->setScene(m_pScene);

	m_pView->setMouseTracking(true);

	m_pHbox->addWidget(m_pView);
	this->setLayout(m_pHbox);

    this->resize(600, 400);

	g_pQtGameEditorSys->setGraphicsScenePtr(m_pScene);
	g_pQtGameEditorSys->setGraphicsViewPtr(m_pView);
}

void DragWidget::makeDraggable(QGraphicsItem *item)
{
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    item->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

DragWidget::~DragWidget()
{

}

void DragWidget::addMultiPolygon()
{
	QPolygonF polygon;
	qreal side = 20;
	qreal dx = qSqrt(3) / 2 * side;
	polygon
		// standing on a point
		<< QPointF(dx, -side / 2)
		<< QPointF(0, -side)
		<< QPointF(-dx, -side / 2)
		<< QPointF(-dx, side / 2)
		<< QPointF(0, side)
		<< QPointF(dx, side / 2);
	// Sitting flat
	//            << QPointF(-side/2, dx)
	//            << QPointF(-side, 0)
	//            << QPointF(-side/2, -dx)
	//            << QPointF(side/2, -dx)
	//            << QPointF(side, 0)
	//            << QPointF(side/2, dx);

	int h = 9;
	int w = 17;
	int mid_h = h / 2;
	int mid_w = w / 2;

	for (int r = 0; r < h; r++)
	{
		for (int c = 0; c < w; c++)
		{
			if (qAbs(mid_h - r) + qAbs(mid_w - c) > 8
				|| (r % 2 != c % 2))
			{
				// don't add a hexagon, it isn't on the board!
			}
			else
			{
				BoardHexagon * hexagon = new BoardHexagon(0);
				hexagon->setPolygon(polygon);
				m_pScene->addItem(hexagon);
				hexagon->setPos(dx * c, side * 1.5 * r);
				hexagon->setToolTip(QString::number(r) + "," + QString::number(c));
			}
		}
	}
}

void DragWidget::addEllipse()
{
	QGraphicsEllipseItem * ellipse = m_pScene->addEllipse(-20, -20, 20, 20, QPen(), QBrush(QColor(Qt::green)));
	this->makeDraggable(ellipse);
}

void DragWidget::addDragWidget()
{
	DraggableItemBase* pDragItem = new DraggableItemBase();
	m_pScene->addItem(pDragItem);
	this->makeDraggable(pDragItem);
}

void DragWidget::addBezierCurve()
{
	BezierCurveItem* pBezierCurveItem = new BezierCurveItem();
	m_pScene->addItem(pBezierCurveItem);
	this->makeDraggable(pBezierCurveItem);
}
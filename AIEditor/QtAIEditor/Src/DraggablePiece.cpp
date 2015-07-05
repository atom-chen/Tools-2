#include "DraggablePiece.h"
#include <QDrag>
#include <QMimeData>
#include <QPainter>

DraggablePiece::DraggablePiece()
{

}

QRectF DraggablePiece::boundingRect() const
{
	qreal adjust = 0.5;
	return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}

void DraggablePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawRect(0, 0, 200, 200);
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QMimeData *data = new QMimeData;
	QVariant variant = QVariant::fromValue((int)Qt::green);
	data->setColorData(variant);

	QDrag *drag = new QDrag((QObject*)event->widget());
    drag->setMimeData(data);
    drag->start();
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
#ifndef __DRAGGABLEPIECE_H
#define __DRAGGABLEPIECE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class DraggablePiece : public QGraphicsItem
{
public:
    DraggablePiece();
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};

class RectItem : public DraggablePiece
{

};

#endif // DRAGGABLEPIECE_H
#include "RecvDropRectItem.h"
#include <QDebug>
#include <QBrush>

RecvDropRectItem::RecvDropRectItem(QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
	this->setBrush(QBrush(Qt::darkGreen));
}

void RecvDropRectItem::focusInEvent(QFocusEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
}

void RecvDropRectItem::focusOutEvent(QFocusEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
}

void RecvDropRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
    this->setBrush(QBrush(Qt::cyan));
}

void RecvDropRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
    this->setBrush(QBrush());
}

void RecvDropRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
}

void RecvDropRectItem::dragEnterEvent(QGraphicsSceneDragDropEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;

    this->setBrush(QBrush(Qt::cyan));
}

void RecvDropRectItem::dragLeaveEvent(QGraphicsSceneDragDropEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
    this->setBrush(QBrush());
}

void RecvDropRectItem::dragMoveEvent(QGraphicsSceneDragDropEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
}

void RecvDropRectItem::dropEvent(QGraphicsSceneDragDropEvent*)
{
    qDebug() << this->toolTip() << Q_FUNC_INFO;
}
#ifndef __RecvDropRectItem_H
#define __RecvDropRectItem_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QFocusEvent>
#include <QGraphicsItem>
//#include <QGraphicsScene>

/**
 *@brief 接收鼠标拖拽的矩形区域，因为在 QGraphicsView 如果要接收拖放事件，必须有一个 QGraphicsItem 才行，因此添加这个
 */
class RecvDropRectItem : public QGraphicsRectItem
{
public:
	RecvDropRectItem(QGraphicsItem *parent = 0);
	~RecvDropRectItem(){}
    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*);
    void dropEvent(QGraphicsSceneDragDropEvent *);
};

#endif // BOARDHEXAGON_H
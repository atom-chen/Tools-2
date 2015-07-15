#ifndef __RecvDropRectItem_H
#define __RecvDropRectItem_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QFocusEvent>
#include <QGraphicsItem>
//#include <QGraphicsScene>

/**
 *@brief ���������ק�ľ���������Ϊ�� QGraphicsView ���Ҫ�����Ϸ��¼���������һ�� QGraphicsItem ���У����������
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
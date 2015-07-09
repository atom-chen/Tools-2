#ifndef __GRAPHICSSCENE_H
#define __GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

protected:
	QPointF m_lastPos;

public:
    explicit GraphicsScene(QObject *parent = 0);

//signals:

//public slots :

public:
	void addGraphicsObject(QGraphicsObject* pQGraphicsObject);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *evt);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * m);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *evt);
};

#endif // GRAPHICSSCENE_H
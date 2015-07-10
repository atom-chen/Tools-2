#ifndef __ActionEffectEditor_H
#define __ActionEffectEditor_H

#include "MyTabSubWidgetBase.h"

#include <QWidget>
#include <QGraphicsItem>

class QHBoxLayout;
class GraphicsView;
class GraphicsScene;

class ActionEffectEditor : public MyTabSubWidgetBase
{
	Q_OBJECT

protected:
	QHBoxLayout * m_pHbox;
	GraphicsView * m_pView;
	GraphicsScene * m_pScene;

public:
	ActionEffectEditor(QWidget *parent = 0);
	~ActionEffectEditor();

	void makeDraggable(QGraphicsItem *);

protected:
	void addMultiPolygon();
	void addEllipse();
	void addDragWidget();
	void addBezierCurve();
};

#endif
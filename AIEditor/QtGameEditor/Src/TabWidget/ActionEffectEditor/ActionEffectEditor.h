#ifndef __ActionEffectEditor_H
#define __ActionEffectEditor_H

#include "MyTabSubWidgetBase.h"

#include <QWidget>
#include <QGraphicsItem>
#include <QtDesigner/QtDesigner>

class MyGraphicsView;
class MyGraphicsScene;
class NodeDockWidget;

class ActionEffectEditor : public MyTabSubWidgetBase
{
	Q_OBJECT

protected:
	MyGraphicsView * m_pView;
	MyGraphicsScene * m_pScene;
	NodeDockWidget* m_pNodeDockWidget;

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
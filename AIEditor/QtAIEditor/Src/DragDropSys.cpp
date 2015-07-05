#include "DragDropSys.h"
#include "BuildFactory.h"
#include "QtAIEditorSys.h"
#include "BezierCurveItem.h"
#include "BuildFactory.h"

DragDropSys::DragDropSys()
{
	m_startDrag = false;
}

DragDropSys::~DragDropSys()
{

}

void DragDropSys::startDrag(QPoint* pStartPt)
{
	m_startDrag = true;

	if (m_pBezierCurveItem == nullptr)
	{
		m_pBezierCurveItem = g_pQtAIEditorSys->m_pBuildFactory->buildBezierCurveItem();
	}
	m_pBezierCurveItem->setStartPos(pStartPt);
}

void DragDropSys::stopDrag()
{
	m_startDrag = false;
	m_pDragItem = nullptr;
	m_pBezierCurveItem = nullptr;
}

void DragDropSys::drog()
{
	m_startDrag = false;
	m_pDragItem = nullptr;
	m_pBezierCurveItem = nullptr;
}

BezierCurveItem* DragDropSys::getBezierCurveItem()
{
	return m_pBezierCurveItem;
}
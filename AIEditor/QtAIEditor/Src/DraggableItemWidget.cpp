#include "DraggableItemWidget.h"
#include "ui_DraggableItemWidget.h"
#include "QtAIEditorSys.h"
//#include <QtCore/QObject>
#include "DragDropSys.h"
#include "DraggableItemBase.h"

DraggableItemWidget::DraggableItemWidget(QWidget *parent)
	: QWidget(parent, 0), m_ui(new Ui::DraggableItemWidget)
{
	m_ui->setupUi(this);

	connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(onClkBtn()));
}

DraggableItemWidget::~DraggableItemWidget()
{

}

void DraggableItemWidget::onClkBtn()
{
	QPoint pStartPt(0, 0);
	QPointF pStartPtF(0, 0);
	//pStartPt = this->mapToGlobal(pStartPt);
	//this->cursor
	pStartPt = QCursor::pos();		// 获取光标位置
	pStartPt = this->mapFromGlobal(pStartPt);	// 转换到窗口空间位置

	pStartPtF.setX(pStartPt.x());	// 设置起始位置
	pStartPtF.setY(pStartPt.y());

	pStartPtF = m_pDraggableItemBase->mapToScene(pStartPtF); // 转换到场景中的位置，场景中的位置都是 Float，屏幕位置都是 Int 类型
	pStartPt.setX(pStartPtF.x());
	pStartPt.setY(pStartPtF.y());
	g_pDragDropSys->startDrag(&pStartPt);
}

void DraggableItemWidget::setDraggableItemBase(DraggableItemBase* pDraggableItemBase)
{
	m_pDraggableItemBase = pDraggableItemBase;
}
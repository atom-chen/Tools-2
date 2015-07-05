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
	pStartPt = QCursor::pos();		// ��ȡ���λ��
	pStartPt = this->mapFromGlobal(pStartPt);	// ת�������ڿռ�λ��

	pStartPtF.setX(pStartPt.x());	// ������ʼλ��
	pStartPtF.setY(pStartPt.y());

	pStartPtF = m_pDraggableItemBase->mapToScene(pStartPtF); // ת���������е�λ�ã������е�λ�ö��� Float����Ļλ�ö��� Int ����
	pStartPt.setX(pStartPtF.x());
	pStartPt.setY(pStartPtF.y());
	g_pDragDropSys->startDrag(&pStartPt);
}

void DraggableItemWidget::setDraggableItemBase(DraggableItemBase* pDraggableItemBase)
{
	m_pDraggableItemBase = pDraggableItemBase;
}
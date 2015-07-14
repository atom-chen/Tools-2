#include "DragDropItemWidget.h"

DragDropItemWidget::DragDropItemWidget(QWidget *parent, int width_)
	: QWidget(parent)
{
	this->setGeometry(QRect(0, 0, width_, 30));

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QStringLiteral("pushButton"));
	m_pBtn->setGeometry(QRect(0, 0, width_, 30));
}

DragDropItemWidget::~DragDropItemWidget()
{

}

void DragDropItemWidget::changgeSize(int width_)
{
	QRect pRect;
	pRect = m_pBtn->geometry();
	m_pBtn->setGeometry(pRect.x(), pRect.y(), width_, pRect.height());

	pRect = this->geometry();
	this->setGeometry(pRect.x(), pRect.y(), width_, pRect.height());
}
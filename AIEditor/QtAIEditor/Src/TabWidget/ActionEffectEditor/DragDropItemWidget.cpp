#include "DragDropItemWidget.h"

DragDropItemWidget::DragDropItemWidget(QWidget *parent)
	: QWidget(parent)
{
	this->setGeometry(QRect(0, 0, 300, 30));

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QStringLiteral("pushButton"));
	m_pBtn->setGeometry(QRect(0, 0, 200, 30));
}

DragDropItemWidget::~DragDropItemWidget()
{

}
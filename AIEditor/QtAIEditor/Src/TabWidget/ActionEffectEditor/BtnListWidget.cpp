#include "BtnListWidget.h"

BtnListWidget::BtnListWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pVbox = new QVBoxLayout;

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QString::fromUtf8("pushButton"));
	m_pBtn->setGeometry(QRect(0, 50, 200, 23));
	m_pVbox->addWidget(m_pBtn);
	//m_pListWidget = new QListWidget(this);
	//m_pListWidget->setGeometry(QRect(0, 80, 300, 23));
	//m_pVbox->addWidget(m_pListWidget);

	this->setLayout(m_pVbox);
	//this->resize(600, 400);
}

BtnListWidget::~BtnListWidget()
{

}
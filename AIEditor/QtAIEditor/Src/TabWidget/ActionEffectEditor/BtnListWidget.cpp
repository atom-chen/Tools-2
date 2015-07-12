#include "BtnListWidget.h"

BtnListWidget::BtnListWidget(QWidget *parent)
	: QWidget(parent)
{
	this->setGeometry(QRect(0, 300, 300, 150));

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QStringLiteral("pushButton"));
	m_pBtn->setGeometry(QRect(20, 20, 200, 30));
	m_pListWidget = new QListWidget(this);
	m_pListWidget->setGeometry(QRect(20, 50, 300, 100));

	QListWidgetItem* item1;
	item1 = new QListWidgetItem("BlueHills", m_pListWidget);//向widget列表中加入一项
	item1 = new QListWidgetItem("Sunset", m_pListWidget);
	item1 = new QListWidgetItem("Water lilies", m_pListWidget);
	item1 = new QListWidgetItem("Himaliya is a good place", m_pListWidget);
	item1 = new QListWidgetItem("Ooty", m_pListWidget);
	item1 = new QListWidgetItem("Hero Honda", m_pListWidget);
	item1 = new QListWidgetItem("www.google.com", m_pListWidget);
	item1 = new QListWidgetItem("orkut.com", m_pListWidget);
	item1 = new QListWidgetItem("sunrise", m_pListWidget);
	item1 = new QListWidgetItem("OVI", m_pListWidget);
	item1 = new QListWidgetItem("Nokia N97", m_pListWidget);
	item1 = new QListWidgetItem("forum.nokia.com", m_pListWidget);
	item1 = new QListWidgetItem("wellcome to Qt", m_pListWidget);
	item1 = new QListWidgetItem("Qt rocks for s60", m_pListWidget);
	item1 = new QListWidgetItem("Symbian c++", m_pListWidget);
	item1 = new QListWidgetItem("5800 Xpress Music", m_pListWidget);
	item1 = new QListWidgetItem("My best Phone", m_pListWidget);
	item1 = new QListWidgetItem("I like N97", m_pListWidget);
	item1 = new QListWidgetItem("Go for 5800", m_pListWidget);
	item1 = new QListWidgetItem("America", m_pListWidget);
}

BtnListWidget::~BtnListWidget()
{

}
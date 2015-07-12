#include "NodeDockWidget.h"
#include "BtnListWidget.H"

NodeDockWidget::NodeDockWidget(QWidget *parent)
	: QDockWidget(parent)
{
	m_pHbox = new QVBoxLayout;
	QWidget* dockWidgetContents = new QWidget();
	this->setWidget(dockWidgetContents);

	m_pQScrollArea = new QScrollArea(dockWidgetContents);
	//m_pQScrollArea->setBackgroundRole(QPalette::Dark);
	//m_pQScrollArea->setMinimumSize(100, 100);
	//m_pQScrollArea->setWidgetResizable(true);
	//m_pQScrollArea->show();
	BtnListWidget* pBtnWidget = new BtnListWidget(m_pQScrollArea);
	//m_pQScrollArea->setWidget(pBtnWidget);//这里设置滚动窗口qw，
	//m_pQScrollArea->setGeometry(0, 0, 200, 200);//要显示的区域大小
	//pBtnWidget->setGeometry(0, 0, 300, 300);//这里变大后，看出他实际滚动的是里面的QWidget窗
	m_pHbox->addWidget(m_pQScrollArea);

	dockWidgetContents->setLayout(m_pHbox);
	//this->resize(600, 400);
}

NodeDockWidget::~NodeDockWidget()
{

}
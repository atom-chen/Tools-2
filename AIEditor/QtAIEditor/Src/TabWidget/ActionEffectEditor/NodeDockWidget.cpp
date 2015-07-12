#include "NodeDockWidget.h"
#include "BtnListWidget.h"
#include "MyScrollAreaWidget.h"

NodeDockWidget::NodeDockWidget(QWidget *parent)
	: QDockWidget(parent)
{
	m_pHbox = new QGridLayout;
	QWidget* dockWidgetContents = new QWidget();
	this->setWidget(dockWidgetContents);

	m_pScrollArea = new MyScrollAreaWidget(dockWidgetContents);
	m_pHbox->addWidget(m_pScrollArea);

	dockWidgetContents->setLayout(m_pHbox);
	//this->resize(600, 400);
}

NodeDockWidget::~NodeDockWidget()
{

}
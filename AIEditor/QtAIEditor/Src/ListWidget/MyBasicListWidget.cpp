#include "MyBasicListWidget.h"

MyBasicListWidget::MyBasicListWidget(QWidget *parent)
	: QWidget(parent)
{
	m_label = new QLabel;
	m_label->setFixedWidth(70);
	m_label->setText(QStringLiteral("²âÊÔÁÐ±í"));
	m_list = new QListWidget;
	m_list->addItem(new QListWidgetItem(QIcon(":/images/line.PNG"), tr("Line")));
	m_list->addItem(new QListWidgetItem(QIcon(":/images/rect.PNG"), tr("Rectangle")));
	m_list->addItem(new QListWidgetItem(QIcon(":/images/oval.PNG"), tr("Oval")));
	m_list->addItem(new QListWidgetItem(QIcon(":/images/tri.PNG"), tr("Triangle")));
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(m_label);
	layout->addWidget(m_list);

	setLayout(layout);

	//connect(m_list, SIGNAL(currentTextChanged(QString)), m_label, SLOT(setText(QString)));
}

void MyBasicListWidget::setViewMode(QListView::ViewMode mode)
{
	m_list->setViewMode(QListView::IconMode);
}
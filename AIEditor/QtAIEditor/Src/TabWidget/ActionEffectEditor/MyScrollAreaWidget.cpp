#include "MyScrollAreaWidget.h"

MyScrollAreaWidget::MyScrollAreaWidget(QWidget *parent)
	: QScrollArea(parent)
{
	test2f();
}

MyScrollAreaWidget::~MyScrollAreaWidget()
{

}

void MyScrollAreaWidget::test1f()
{
	//this->setBackgroundRole(QPalette::Dark);
	//this->setMinimumSize(200, 200);
	this->setAlignment(Qt::AlignLeft);
	//this->setWidgetResizable(true);
	//this->show();
	//BtnListWidget* pBtnWidget = new BtnListWidget(m_pQScrollArea);
	//this->setWidget(pBtnWidget);//这里设置滚动窗口qw，
	//this->setGeometry(0, 0, 2000, 2000);//要显示的区域大小
	//pBtnWidget->setGeometry(0, 0, 300, 300);//这里变大后，看出他实际滚动的是里面的QWidget窗

	QVBoxLayout* pHbox = new QVBoxLayout;
	//pHbox->addSpacing(0);
	pHbox->addStretch(100);

	QPushButton* pBtn = new QPushButton(this);
	pBtn->setGeometry(0, 0, 2000, 2000);
	pBtn->setMinimumSize(100, 30);
	//pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	pBtn = new QPushButton(this);
	pBtn->setMinimumSize(100, 30);
	pHbox->addWidget(pBtn);
	//this->setLayout(pHbox);
}

void MyScrollAreaWidget::test2f()
{
	QWidget* content = new QWidget();
	content->setMinimumHeight(280);
	//content->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

	QVBoxLayout* vlayout = new QVBoxLayout(content);
	//scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vlayout->addWidget(createGroupBox("box1", 3));
	vlayout->addWidget(createGroupBox("box2", 5));
	vlayout->addStretch(1);

	this->setWidget(content);
}

QWidget* MyScrollAreaWidget::createGroupBox(const QString& title, int n)
{
	QGroupBox* box = new QGroupBox(title);
	QVBoxLayout* boxlayout = new QVBoxLayout(box);
	for (int i = 0; i<n; i++)
		boxlayout->addWidget(new QRadioButton(QString("%1").arg(i)));

	return box;
}
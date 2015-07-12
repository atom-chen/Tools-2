#include "TestQScrollArea1F.h"

TestQScrollArea1F::TestQScrollArea1F(QWidget* parent, Qt::WindowFlags flags) :
	QWidget(parent, flags)
{
	createWidget();
}

TestQScrollArea1F::~TestQScrollArea1F()
{
}

void TestQScrollArea1F::createWidget()
{
	resize(300, 360);

	QGridLayout* gridLayout = new QGridLayout(this);
	QScrollArea* scrollArea = new QScrollArea(this);
	//scrollArea->setWidgetResizable(false);
	//scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	QWidget* scrollAreaWidgetContents = new QWidget();
	//scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 251));
	scrollArea->setWidget(scrollAreaWidgetContents);

	gridLayout->addWidget(scrollArea, 0, 0, 1, 2);

	QSpacerItem* horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

	QPushButton* pushButton = new QPushButton(this);
	pushButton->setText("OK");
	gridLayout->addWidget(pushButton, 1, 1, 1, 1);

	QWidget* content = new QWidget();
	content->setMinimumHeight(280);
	//content->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

	QVBoxLayout* vlayout = new QVBoxLayout(content);
	//scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	vlayout->addWidget(createGroupBox("box1", 3));
	vlayout->addWidget(createGroupBox("box2", 5));
	vlayout->addStretch(1);

	scrollArea->setWidget(content);
	//scrollArea->setFixedHeight(420);
}

QWidget* TestQScrollArea1F::createGroupBox(const QString& title, int n)
{
	QGroupBox* box = new QGroupBox(title);
	QVBoxLayout* boxlayout = new QVBoxLayout(box);
	for (int i = 0; i<n; i++)
		boxlayout->addWidget(new QRadioButton(QString("%1").arg(i)));

	return box;
}
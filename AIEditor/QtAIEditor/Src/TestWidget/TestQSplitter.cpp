#include "TestQSplitter.h"

TestQSplitter::TestQSplitter(QWidget* parent, Qt::WindowFlags flags) :
	QWidget(parent, flags)
{
	//testNoLayout();
	testLayout();
}

TestQSplitter::~TestQSplitter()
{

}

void TestQSplitter::testNoLayout()
{
	QSplitter * mainSplitter = new QSplitter(Qt::Horizontal, this);
	mainSplitter->setHandleWidth(10);
	mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //���÷ֽ��ߵ���ʽ  
	QLabel *label = new QLabel(QObject::tr("TestA"));
	QLabel *label2 = new QLabel(QObject::tr("TestB"));

	mainSplitter->addWidget(label2);
	mainSplitter->addWidget(label);
	mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//mainSplitter->show();
}

void TestQSplitter::testLayout()
{
	QHBoxLayout* m_pHbox = new QHBoxLayout;
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	QSplitter * mainSplitter = new QSplitter(Qt::Horizontal, this);
	mainSplitter->setHandleWidth(10);
	mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //���÷ֽ��ߵ���ʽ  
	QLabel *label = new QLabel(QObject::tr("TestA"));
	QLabel *label2 = new QLabel(QObject::tr("TestB"));

	mainSplitter->addWidget(label2);
	mainSplitter->addWidget(label);
	mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//mainSplitter->show();

	m_pHbox->addWidget(mainSplitter);
	this->setLayout(m_pHbox);
}
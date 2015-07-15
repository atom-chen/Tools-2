#include "TestQSplitter.h"
#include "MyBasicListWidget.h"
#include "MyBasicMVCTreeWidget.h"

TestQSplitter::TestQSplitter(QWidget* parent, Qt::WindowFlags flags) :
	QWidget(parent, flags)
{
	//testNoLayout();
	//testLayout();
	testLayoutList();
}

TestQSplitter::~TestQSplitter()
{

}

void TestQSplitter::testNoLayout()
{
	QSplitter * mainSplitter = new QSplitter(Qt::Horizontal, this);
	mainSplitter->setHandleWidth(10);
	mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式  
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
	mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式  
	QLabel *label = new QLabel(QObject::tr("TestA"));
	QLabel *label2 = new QLabel(QObject::tr("TestB"));

	mainSplitter->addWidget(label2);
	mainSplitter->addWidget(label);
	mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//mainSplitter->show();

	m_pHbox->addWidget(mainSplitter);
	this->setLayout(m_pHbox);
}

void TestQSplitter::testLayoutList()
{
	QHBoxLayout* m_pHbox = new QHBoxLayout;
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	QSplitter * mainSplitter = new QSplitter(Qt::Horizontal, this);
	mainSplitter->setHandleWidth(10);
	mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式  
	MyBasicMVCTreeWidget* _pTreeWidget = new MyBasicMVCTreeWidget;
	MyBasicListWidget* _pListWidget = new MyBasicListWidget;

	mainSplitter->addWidget(_pListWidget);
	_pTreeWidget->add2Splitter(mainSplitter);
	mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//mainSplitter->show();

	m_pHbox->addWidget(mainSplitter);
	this->setLayout(m_pHbox);
}
#include "MyTabMainWindow.h"
#include "MyTabWidget.h"
#include "MyTabSubWidgetFrame.h"
#include <QtGui>
#include "ActionEffectEditor.h"
#include "UtilEncode.h"

MyTabMainWindow::MyTabMainWindow(QWidget *parent) :QMainWindow(parent)
{
	m_pTabWidget = new MyTabWidget(this);
	//Ìí¼Ó4¸ötabÒ³
	//addTestWindow();
	setCentralWidget(m_pTabWidget);

	connect(m_pTabWidget->m_tabBar, SIGNAL(sig_tabDrag(int, QPoint)), this, SLOT(slot_tabDrag(int, QPoint)));
	connect(m_pTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_closeTab(int)));
	connect(m_pTabWidget, SIGNAL(currentChanged(int)), m_pTabWidget, SLOT(setCurrentIndex(int)));

	resize(800, 600);
}

void MyTabMainWindow::slot_tabDrag(int index, QPoint point)
{
	MyTabSubWidgetFrame *widget = new MyTabSubWidgetFrame;
	QWidget *draged = m_pTabWidget->widget(index);
	QString windowName = m_pTabWidget->tabText(index);
	m_pTabWidget->removeTab(index);
	connect(widget, SIGNAL(sig_doubleClickedTitleBar()), this, SLOT(slot_tabBarDoubleClicked()));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(draged);
	widget->setLayout(layout);
	widget->resize(600, 400);
	widget->move(point + pos() + m_pTabWidget->pos());
	widget->setWindowTitle(windowName);
	widget->show();
	draged->show();

	m_frameVec.push_back(static_cast<MyTabSubWidgetBase*>(draged));
}

void MyTabMainWindow::slot_tabBarDoubleClicked()
{
	MyTabSubWidgetFrame *widget = qobject_cast<MyTabSubWidgetFrame*>(sender());
	QObjectList list = widget->children();
	//QTextEdit *edit = NULL;
	MyTabSubWidgetBase* subWidget;

	for (int i = 0; i<list.count(); ++i)
	{
		//if (list[i]->inherits("QTextEdit"))
		if (list[i]->inherits("MyTabSubWidgetBase"))
		{
			//edit = qobject_cast<QTextEdit*>(list[i]);
			subWidget = qobject_cast<MyTabSubWidgetBase*>(list[i]);
			break;
		}
	}
	//if (edit == NULL)
	if (subWidget == nullptr)
	{
		return;
	}

	//edit->setParent(m_pTabWidget);
	//m_pTabWidget->addTab(edit, widget->windowTitle());
	subWidget->setParent(m_pTabWidget);
	m_pTabWidget->addTab(subWidget, widget->windowTitle());
	delete widget;
	removeOneEditor(subWidget->getFullPath());
}

void MyTabMainWindow::slot_closeTab(int index)
{
	QWidget *draged = m_pTabWidget->widget(index);
	m_pTabWidget->removeTab(index);
	delete draged;
}

void MyTabMainWindow::addTestWindow()
{
	m_pTabWidget->addTab(new QTextEdit, "eidt 1");
	m_pTabWidget->addTab(new QTextEdit, "eidt 2");
	m_pTabWidget->addTab(new QTextEdit, "eidt 3");
	m_pTabWidget->addTab(new QTextEdit, "eidt 4");
}

void MyTabMainWindow::openOneActionEffectEditor(std::string path)
{
	ActionEffectEditor* m_actionEffectWidget = new ActionEffectEditor();
	m_actionEffectWidget->setFullPath(path);
	m_pTabWidget->addTab(m_actionEffectWidget, UtilEncode::sLocal2QUnicode(path));
	//m_frameVec.push_back(m_actionEffectWidget);
}

void MyTabMainWindow::removeOneEditor(std::string path)
{
	TabSubWidgetIte iteBegin, iteEnd;
	iteBegin = m_frameVec.begin();
	iteEnd = m_frameVec.end();
	for (; iteBegin != iteEnd; ++iteBegin)
	{
		if ((*iteBegin)->getFullPath() == path)
		{
			m_frameVec.erase(iteBegin);
		}
	}
}
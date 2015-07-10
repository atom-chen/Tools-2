#include "MyTabMainWindow.h"
#include "MyTabWidget.h"
#include "MyTabSubWidgetFrame.h"
#include <QtGui>

MyTabMainWindow::MyTabMainWindow(QWidget *parent) :QMainWindow(parent)
{
	tabWidget = new MyTabWidget(this);
	tabWidget->setMovable(true);
	tabWidget->setTabsClosable(true);
	tabWidget->setTabShape(QTabWidget::Triangular);
	//Ìí¼Ó4¸ötabÒ³
	tabWidget->addTab(new QTextEdit, "eidt 1");
	tabWidget->addTab(new QTextEdit, "eidt 2");
	tabWidget->addTab(new QTextEdit, "eidt 3");
	tabWidget->addTab(new QTextEdit, "eidt 4");
	setCentralWidget(tabWidget);

	connect(tabWidget->tabBar, SIGNAL(sig_tabDrag(int, QPoint)), this, SLOT(slot_tabDrag(int, QPoint)));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_closeTab(int)));
	connect(tabWidget, SIGNAL(currentChanged(int)), tabWidget, SLOT(setCurrentIndex(int)));

	resize(800, 600);
}

void MyTabMainWindow::slot_tabDrag(int index, QPoint point)
{
	MyTabSubWidgetFrame *widget = new MyTabSubWidgetFrame;
	QWidget *draged = tabWidget->widget(index);
	QString windowName = tabWidget->tabText(index);
	tabWidget->removeTab(index);
	connect(widget, SIGNAL(sig_doubleClickedTitleBar()), this, SLOT(slot_tabBarDoubleClicked()));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(draged);
	widget->setLayout(layout);
	widget->resize(600, 400);
	widget->move(point + pos() + tabWidget->pos());
	widget->setWindowTitle(windowName);
	widget->show();
	draged->show();
}

void MyTabMainWindow::slot_tabBarDoubleClicked()
{
	MyTabSubWidgetFrame *widget = qobject_cast<MyTabSubWidgetFrame*>(sender());
	QObjectList list = widget->children();
	QTextEdit *edit = NULL;

	for (int i = 0; i<list.count(); ++i)
	{
		if (list[i]->inherits("QTextEdit"))
		{
			edit = qobject_cast<QTextEdit*>(list[i]);
			break;
		}
	}
	if (edit == NULL)
	{
		return;
	}

	edit->setParent(tabWidget);
	tabWidget->addTab(edit, widget->windowTitle());
	delete widget;
}

void MyTabMainWindow::slot_closeTab(int index)
{
	QWidget *draged = tabWidget->widget(index);
	tabWidget->removeTab(index);
	delete draged;
}
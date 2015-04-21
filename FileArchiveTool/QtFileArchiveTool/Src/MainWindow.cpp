#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LogWidget.h"
#include "ProjectWidget.h"
#include "CenterTabWidget.h"
#include "QtFileArchiveToolSys.h"
#include "ArchiveData.h"
#include "ThreadPool.h"

#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent, 0), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	//���������ڱ���
	setWindowTitle(QStringLiteral("FileArchiveTool"));
	setDockNestingEnabled(true);

	insGlobal();
	createActions();
	createMenus();
	createToolBars();

	connectAction();
	createDockWidget();
	createTimer();
}

MainWindow::~MainWindow()
{

}

// ʵ����ȫ�ֱ���
void MainWindow::insGlobal()
{
	QtFileArchiveToolSysDef;
	QtFileArchiveToolSysDef->init();
}

void MainWindow::createDockWidget()
{
	m_projectWidget = new ProjectWidget(this);
	this->addDockWidget(Qt::LeftDockWidgetArea, m_projectWidget);

	QObject::connect(m_projectWidget, SIGNAL(onTreeItemSelChange(bool, std::string)), this, SLOT(onTreeItemSelChange(bool, std::string)));
	QObject::connect(m_projectWidget, SIGNAL(visibilityChanged(bool)), this, SLOT(onProjectVisibilityChanged(bool)));

	// BEGIN
	// ������������
	//m_centerTabWidget = new CenterTabWidget(this);
	//setCentralWidget(m_centerTabWidget);

	//m_logWidget = new LogWidget(this);
	//this->addDockWidget(Qt::BottomDockWidgetArea, m_logWidget);
	// END

	// BEGIN
	// ���� tab �Ӵ�����
	//m_centerTabWidget = new CenterTabWidget(this);
	//setCentralWidget(m_centerTabWidget);
	//m_pSubMainWin = new QMainWindow(m_centerTabWidget);
	//m_centerTabWidget->addTab(m_pSubMainWin, tr("Text Editor"));
	// END

	// BEGIN
	// �����Ӵ�����
	m_pSubMainWin = new QMainWindow(this);
	m_pSubMainWin->setWindowFlags(Qt::Widget);		// KBEN: ���б���Ҫ�������ܿ��� QMainWindow �Ӵ���
	this->setCentralWidget(m_pSubMainWin);

	m_centerTabWidget = new CenterTabWidget(m_pSubMainWin);
	m_pSubMainWin->setCentralWidget(m_centerTabWidget);

	m_logWidget = new LogWidget(m_pSubMainWin);
	m_pSubMainWin->addDockWidget(Qt::BottomDockWidgetArea, m_logWidget);
	// END

	QtFileArchiveToolSysDef->getLogSysPtr()->regLogDevice(m_logWidget);
	//QtFileArchiveToolSysDef->getLogSysPtr()->log("���");
}

void MainWindow::createActions()
{
	//ͨ��ͼƬ·����ʵ�����Qt��Դ�ļ�Ŀ��
	fileOpenAction = new QAction(QIcon(":/Icons/open.png"),tr("Open"),this);
	fileOpenAction->setShortcut(tr("Ctrl+O"));
	fileOpenAction->setStatusTip(tr("Open a file"));
	QObject::connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));

	fileNewAction = new QAction(QIcon(":/Icons/new.png"),tr("New"),this);
	fileNewAction->setShortcut(tr("Ctrl+N"));
	fileNewAction->setStatusTip(tr("new file"));
	QObject::connect(fileNewAction, SIGNAL(triggered()), this, SLOT(slotNewFile()));
  
	fileSaveAction = new QAction(QIcon(":/Icons/save.png"),tr("Save"),this);
	fileSaveAction->setShortcut(tr("Ctrl+S"));
	fileNewAction->setStatusTip(tr("save file"));
	QObject::connect(fileNewAction, SIGNAL(triggered()), this, SLOT(slotSaveFile()));

	exitAction = new QAction(tr("Exit"),this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("exit"));
	QObject::connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	cutAction = new QAction(QIcon(":/Icons/cut.png"),tr("Cut"),this);
	cutAction->setShortcut(tr("Ctrl+X"));
	cutAction->setStatusTip(tr("cut to clipboard"));
	QObject::connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

	copyAction = new QAction(QIcon(":/Icons/copy.png"),tr("Copy"),this);
	copyAction->setShortcut(tr("Ctrl+C"));
	copyAction->setStatusTip(tr("copy to clipboard"));
	QObject::connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

	pasteAction = new QAction(QIcon(":/Icons/paste.png"),tr("paste"),this);
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setStatusTip(tr("paste clipboard to selection"));
	QObject::connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

	showProjectAction = new QAction(tr("showProject"), this);
	showProjectAction->setCheckable(true);	// ����Ҫ�ȵ��� setCheckable ��Ȼ����� setChecked ����Ч
	showProjectAction->setChecked(true);	// ���ó�ʼ״̬
	showProjectAction->setShortcut(tr("Shift+V"));
	showProjectAction->setStatusTip(tr("showProject"));
	QObject::connect(showProjectAction, SIGNAL(triggered()), this, SLOT(showProject()));

	showLogAction = new QAction(tr("showLog"), this);
	showLogAction->setCheckable(true);
	showLogAction->setChecked(true);
	showLogAction->setShortcut(tr("Shift+C"));
	showLogAction->setStatusTip(tr("showLog"));
	QObject::connect(showLogAction, SIGNAL(triggered()), this, SLOT(showLog()));

	aboutAction = new QAction(tr("About"), this);
	QObject::connect(aboutAction, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(fileNewAction);
	fileMenu->addAction(fileOpenAction);
	fileMenu->addAction(fileSaveAction);
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("Edit"));
	editMenu->addAction(copyAction);
	editMenu->addAction(cutAction);
	editMenu->addAction(pasteAction);

	viewMenu = menuBar()->addMenu(tr("View"));
	viewMenu->addAction(showProjectAction);
	viewMenu->addAction(showLogAction);

	aboutMenu = menuBar()->addMenu(tr("Help"));
	aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
	fileTool = addToolBar("File");
	fileTool->addAction(fileNewAction);
	fileTool->addAction(fileOpenAction);
	fileTool->addAction(fileSaveAction);

	editTool = addToolBar("Edit");
	editTool->addAction(copyAction);
	editTool->addAction(cutAction);
	editTool->addAction(pasteAction);
}

void MainWindow::slotNewFile()
{
	MainWindow *newWin = new MainWindow;
	newWin->show();
}

void MainWindow::slotOpenFile()
{
	fileName = QFileDialog::getOpenFileName(this);
	if(!fileName.isEmpty())
	{
		if(text->document()->isEmpty())
		{
			loadFile(fileName);
		}
		else
		{
			MainWindow *newWin = new MainWindow;
			newWin->show();
			newWin->loadFile(fileName);
		}
	}
}

void MainWindow::loadFile(QString fileName)
{
	printf("file name:%s\n",fileName.data());
	QFile file(fileName);
	if(file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QTextStream textStream(&file);
		while(!textStream.atEnd())
		{
			text->append(textStream.readLine());
			printf("read line.\n");
		}
		printf("end\n");
	}
}

void MainWindow::connectAction()
{
	QObject::connect(m_ui->actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
}

void MainWindow::onTreeItemSelChange(bool isDir, std::string path)
{
	int aaa = 10;
}

void MainWindow::showProject()
{
	if (!m_projectWidget->isVisible())
	{
		m_projectWidget->show();
		//showProjectAction->setChecked(true);	// Ĭ�������Զ��л��������Լ�����ĳһ��״̬
	}
	else
	{
		m_projectWidget->hide();
	}
}

void MainWindow::showLog()
{
	if (!m_logWidget->isVisible())
	{
		m_logWidget->show();
	}
	else
	{
		m_logWidget->hide();
	}
}

void MainWindow::onProjectVisibilityChanged(bool bVisible)
{

}

void MainWindow::createTimer()
{
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));	// timeoutslot() Ϊ�Զ����
	m_timer->start(1000);
}

void MainWindow::update()
{
	QtFileArchiveToolSysDef->onTick();
}

// �ر��¼�
void MainWindow::closeEvent(QCloseEvent *event)
{
	if (QtFileArchiveToolSysDef->getArchiveDataPtr()->getPakItemCount())	// ������� PakItem û�����
	{
		// ������ʾ
		event->ignore();
		return;
	}

	QtFileArchiveToolSysDef->getThreadPoolPtr()->wait();

	// �ͷ�������Դ

	event->accept();
}
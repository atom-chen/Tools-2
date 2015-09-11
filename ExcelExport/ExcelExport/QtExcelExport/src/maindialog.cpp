#include "maindialog.h"
#include "ui_maindialog.h"
#include "AppSysPrerequisites.h"

//#include <QtGui>	// QtGui
#include <QtCore>	// QVector
#include "TableListItem.h"

#include "MemLeakCheck.h"

BEGIN_NAMESPACE

MainDialog::MainDialog(QWidget *parent)
	: QDialog(parent, Qt::FramelessWindowHint), m_ui(new Ui::Dialog)
{
	m_ui->setupUi(this);

	Qt::WindowFlags flags = 0;
	flags |= Qt::WindowMinimizeButtonHint;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags); // 设置禁止最大化
	this->setFixedSize(630, 700); // 禁止改变窗口大小。
	this->setWindowIcon(QIcon(":/icons/icon.png"));	// 设置窗口图标

	connect(m_ui->pushButtonOutput, SIGNAL(clicked()), this, SLOT(btnOutput()));
	connect(m_ui->pushButtonOutputXml, SIGNAL(clicked()), this, SLOT(btnXml()));
	connect(m_ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(btnStart()));
	connect(m_ui->checkBox, SIGNAL(clicked()), this, SLOT(onChkAllBtnClk()));

	connect(m_ui->m_codePushButton, SIGNAL(clicked()), this, SLOT(onBtnCode()));
	connect(m_ui->m_csCheckBox, SIGNAL(clicked()), this, SLOT(onCSChkBtnClk()));
	connect(m_ui->m_cppCheckBox, SIGNAL(clicked()), this, SLOT(onCPPChkBtnClk()));

	connect(m_ui->TableListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListItemClk(QListWidgetItem*)));

	setWindowTitle(QStringLiteral("Excel打包工具"));
	//this->setWindowFlags(Qt::WindowTitleHint);
	//this->setWindowFlags(Qt::WindowCloseButtonHint);

	// TODO: 设置控件属性 
	m_ui->comboBoxOutput->setInsertPolicy(QComboBox::InsertAtTop);
	m_ui->comboBoxOutput->setEditable(true);

	m_ui->comboBoxOutputXml->setInsertPolicy(QComboBox::InsertAtTop);
	m_ui->comboBoxOutputXml->setEditable(true);

	//m_ui->comboBoxSolution->setEditText("");
	//m_ui->comboBoxSolution->setInsertPolicy(QComboBox::InsertAtTop);
	//m_ui->comboBoxSolution->setEditable(true);

	// init appdata
	g_pAppSys->initData();
	//QThread* pthread = new WorkThread();
	//g_pAppSys->initThread(pthread);
	// fill to comboBoxSolution
	//g_pAppSys->initCombo(m_ui->comboBoxSolution);
	// clear select item,must after initCombo
	//m_ui->comboBoxSolution->setCurrentIndex(-1);

	// TODO: 打表功能测试   
	//m_excelTbl = new ExcelTbl();
	//m_excelTbl = new ExcelTblSort();
	//m_thread.setParam(m_excelTbl);
	//m_thread.setParam(g_pAppSys->getExcelTbl());
	g_pUtils->setParent(this);
	//g_pUtils->setTextEdit(ui->m_outTextEdit);
	// 检测大端小端
	g_pSystem->checkEndian();

	addListItem();

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));	// timeoutslot() 为自定义槽
	m_timer->start(1000);
}

MainDialog::~MainDialog()
{
	m_timer->stop();
	delete m_timer;
	//delete m_excelTbl;

	delete m_ui;
}

void MainDialog::addListItem()
{
	TableListItem *listItemUI;
	QListWidgetItem *listItem;
	std::vector<Table*>& tableList = g_pAppSys->getTask()->getTableList();

	std::vector<Table*>::iterator tableIteVecBegin = tableList.begin();
	std::vector<Table*>::iterator tableIteVecEnd = tableList.end();
	for (; tableIteVecBegin != tableIteVecEnd; ++tableIteVecBegin)
	{
		listItemUI = new TableListItem(this);
		listItem = new QListWidgetItem();
		listItem->setSizeHint(QSize(0, 50));
		listItemUI->setTable(*tableIteVecBegin);
		m_ui->TableListWidget->addItem(listItem);
		m_ui->TableListWidget->setItemWidget(listItem, listItemUI);
	}
}

void MainDialog::btnOutput()
{
	QString dir = "";
	QString filter = "";
	if(m_ui->comboBoxOutput->currentText().length())
	{
		dir = m_ui->comboBoxOutput->currentText();
	}
	else
	{
		dir = QDir::currentPath();
	}

	QString fileName = g_pUtils->openDirectoryDialog(dir);

    if (!fileName.isEmpty()) 
	{
		if (m_ui->comboBoxOutput->findText(fileName) == -1)
			m_ui->comboBoxOutput->addItem(fileName);
		m_ui->comboBoxOutput->setCurrentIndex(m_ui->comboBoxOutput->findText(fileName));
	}
}

void MainDialog::btnXml()
{
	QString dir = "";
	QString filter = "";
	// TODO: 默认过滤器    
	// filter = "All Files (*);;Text Files (*.txt)";
	filter = "All Files (*);;XML Files (*.xml)";
	if (m_ui->comboBoxOutputXml->currentText().length())
	{
		dir = m_ui->comboBoxOutputXml->currentText();
	}

	QString fileName = g_pUtils->openFileDialog(dir, filter);

    if (!fileName.isEmpty()) 
	{
		if (m_ui->comboBoxOutputXml->findText(fileName) == -1)
		{
			m_ui->comboBoxOutputXml->addItem(fileName);
		}
		m_ui->comboBoxOutputXml->setCurrentIndex(m_ui->comboBoxOutputXml->findText(fileName));
	}
}

void MainDialog::btnStart()
{
	QString outPath = m_ui->comboBoxOutput->currentText();
	QString xmlFile = m_ui->comboBoxOutputXml->currentText();
	//QString xmlsolution = m_ui->comboBoxSolution->currentText();

	//g_pAppSys->setXml(outPath.toLocal8Bit().data(), xmlFile.toLocal8Bit().data(), xmlsolution.toLocal8Bit().data());
	//g_pAppSys->setXml(g_pUtils->UNICODEStr2GBKStr(outPath).toLocal8Bit().data(), g_pUtils->UNICODEStr2GBKStr(xmlFile).toLocal8Bit().data(), g_pUtils->UNICODEStr2GBKStr(xmlsolution).toLocal8Bit().data());
	//g_pAppSys->setXml(g_pUtils->UNICODEStr2GBKStr(outPath).toStdString(), g_pUtils->UNICODEStr2GBKStr(xmlFile).toStdString(), g_pUtils->UNICODEStr2GBKStr(xmlsolution).toStdString());
	//g_pAppSys->setXml(outPath.toStdString(), xmlFile.toStdString(), xmlsolution.toStdString());

	//char aaa[256];
	//g_pUtils->UTF8ToGBK((unsigned char *)outPath.toUtf8().data(), (unsigned char *)aaa, 256);
	g_pAppSys->setXml(g_pUtils->UNICODEStr2LocalChar(outPath), g_pUtils->UNICODEStr2LocalChar(xmlFile));

	//if((outPath.length() == 0 || xmlFile.length() == 0) && xmlsolution.length() == 0)
	//{
	//	QString msg = tr("path is empty");
	//	g_pUtils->informationMessage(msg);
	//}
	//else
	//{
		//pushButtonStart.enable = false;

		//QMessageBox::information(this, tr("QMessageBox::information()"), tr("asdasdf"));
		if (!g_pExcelWorkThread->isRunning())
		{
			//m_excelTbl->setXmlPath(xmlFile);
			//m_excelTbl->setOutputPath(outPath);
			//m_thread.start();
			g_pExcelWorkThread->startThread();
			//m_thread.wait();		// 会死锁 
			//pushButtonStart.enable = false;
		}
		else
		{
			g_pUtils->informationMessage(QStringLiteral("正在打表"));
		}
	//}
}

void MainDialog::onBtnCode()
{
	if (!g_pCodeWorkThread->isRunning())
	{
		g_pCodeWorkThread->startThread();
	}
	else
	{
		g_pUtils->informationMessage(QStringLiteral("正在导出代码"));
	}
}

void MainDialog::update()
{
	QVector<QString>& list = g_pUtils->getLog();
	QVector<QString>::Iterator begin = list.begin();
	while(begin != list.end())
	{
		//ui->m_outTextEdit->setPlainText(*begin);
		m_ui->m_outTextEdit->append(*begin);
		++begin;
	}

	// 显示对话框
	list = g_pUtils->getLogMsg();
	begin = list.begin();
	if(begin != list.end())
	{
		g_pUtils->informationMessageUI(*begin);
	}
}

void MainDialog::onChkAllBtnClk()
{
	int idx = 0;
	TableListItem *listItemUI;
	while (idx < m_ui->TableListWidget->count())
	{
		listItemUI = (TableListItem *)m_ui->TableListWidget->itemWidget(m_ui->TableListWidget->item(idx));
		listItemUI->m_ui->checkBox->setChecked(m_ui->checkBox->isChecked());
		listItemUI->onChkBtnClk();
		++idx;
	}
}

void MainDialog::onCSChkBtnClk()
{
	g_pCodeWorkThread->setCsCode(m_ui->m_csCheckBox->isChecked());
}

void MainDialog::onCPPChkBtnClk()
{
	g_pCodeWorkThread->setCppCode(m_ui->m_cppCheckBox->isChecked());
}

void MainDialog::onListItemClk(QListWidgetItem *item)
{
	TableListItem *listItemUI;
	listItemUI = (TableListItem *)m_ui->TableListWidget->itemWidget(item);
	listItemUI->m_ui->checkBox->setChecked(!listItemUI->m_ui->checkBox->isChecked());
	listItemUI->onChkBtnClk();
}

void MainDialog::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		//进行界面退出，重写Esc键，否则重写reject()方法
	case Qt::Key_Escape:
		//this->close();
		break;

	default:
		QDialog::keyPressEvent(event);
	}
}

END_NAMESPACE
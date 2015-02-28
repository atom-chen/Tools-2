#include "LogWidget.h"
#include "ui_LogWidget.h"
#include "QtFileArchiveToolSys.h"

LogWidget::LogWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::LogWidget)
{
	m_ui->setupUi(this);

	this->setWidget(m_ui->verticalLayoutWidget);

	createAction();
	createToolBar();
}

LogWidget::~LogWidget()
{

}

void LogWidget::log(const char* msg)
{
	m_ui->textBrowser->append(QtFileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8Str((char*)msg));
}

void LogWidget::createToolBar()
{
	QToolBar *projectToolBar = new QToolBar(m_ui->verticalLayoutWidget);
	projectToolBar->setObjectName("logToolBar");
	projectToolBar->setIconSize(QSize(20, 20));
	projectToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	projectToolBar->addAction(m_actClear);

	m_ui->verticalLayout->addWidget(projectToolBar);
}

void LogWidget::createAction()
{
	m_actClear = new QAction(tr("Refresh"), this);
	m_actClear->setStatusTip(tr("Refresh List"));
	m_actClear->setIcon(QIcon(":/Icons/new.png"));
	connect(m_actClear, SIGNAL(triggered()), this, SLOT(clearText()));
}

void LogWidget::clearText()
{
	m_ui->textBrowser->clear();
}
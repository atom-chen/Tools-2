#include "LogWidget.h"
#include "ui_LogWidget.h"
#include "QtFileArchiveToolSys.h"

LogWidget::LogWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::LogWidget)
{
	m_ui->setupUi(this);

	this->setWidget(m_ui->verticalLayoutWidget);
}

LogWidget::~LogWidget()
{

}

void LogWidget::log(const char* msg)
{
	m_ui->textBrowser->append(QtFileArchiveToolSysDef->getCharsetConvPtr()->GBKToUTF8Str((char*)msg));
}
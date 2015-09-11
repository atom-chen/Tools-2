#include "TableListItem.h"
#include <QtWidgets/QWidget>
#include "AppSysPrerequisites.h"

#include "MemLeakCheck.h"

BEGIN_NAMESPACE

TableListItem::TableListItem(QWidget *parent)
	: QWidget(parent), m_ui(new Ui::TableListItem)
{
	m_ui->setupUi(this);
	connect(m_ui->checkBox, SIGNAL(clicked()), this, SLOT(onChkBtnClk()));
	//connect(this, SIGNAL(clicked()), this, SLOT(onListItemClk()));
}

void TableListItem::setTable(Table* table)
{
	m_table = table;
	//m_ui->label->setText(g_pUtils->GBKChar2UNICODEStr(m_table->m_strExcelDirAndName.c_str()));
	m_ui->label->setText(m_table->m_lpszTableName.c_str());
}

void TableListItem::onChkBtnClk()
{
	m_table->m_bExportTable = m_ui->checkBox->isChecked();
}

//void TableListItem::onListItemClk()
//{
//	m_ui->checkBox->setChecked(!m_ui->checkBox->isChecked());
//	onChkBtnClk();
//}

END_NAMESPACE
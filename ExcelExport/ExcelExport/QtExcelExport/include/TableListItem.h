#ifndef TABLELISTITEM_H
#define TABLELISTITEM_H

#include <QWidget>
#include "Task.h"
#include "ui_TableListItem.h"

QT_USE_NAMESPACE

namespace Ui
{
	class TableListItem;
}

BEGIN_NAMESPACE

class TableListItem : public QWidget
{
	Q_OBJECT
public:
	Ui::TableListItem *m_ui;

private:
	Table* m_table;

public slots:
	void onChkBtnClk();
	//void onListItemClk();

public:
	explicit TableListItem(QWidget *parent);
	void setTable(Table* table);

signals:
	public slots :
};

END_NAMESPACE

#endif // TABLELISTITEM_H
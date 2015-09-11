#ifndef _MAINDIALOG_H
#define _MAINDIALOG_H

#include <QtWidgets>	// QDialog
#include <iostream>
#include <QtCore>		// QTimer
//#include "WorkThread.h"
//#include "ExcelTbl.h"
#include "Platform.h"

using namespace std;

QT_USE_NAMESPACE

class QListWidgetItem;

namespace Ui
{
	class Dialog;
}

BEGIN_NAMESPACE

class MainDialog : public QDialog
{
	Q_OBJECT

public:
	MainDialog(QWidget *parent = 0);
	~MainDialog();

	void addListItem();

private:
	Ui::Dialog *m_ui;
	//ExcelTbl* m_excelTbl;
	//WorkThread m_thread;
	QTimer *m_timer;
    
private slots:
	void btnOutput();
	void btnXml();
	void btnStart();
//	void exitApp ();
	void update();
	void onChkAllBtnClk();
	void onListItemClk(QListWidgetItem *item);

protected:
	void keyPressEvent(QKeyEvent *event);
};

END_NAMESPACE

#endif // MAINDIALOG_H

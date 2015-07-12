#ifndef __BtnListWidget_H
#define __BtnListWidget_H

#include "QtIncAll.h"

class BtnListWidget : public QWidget
{
	Q_OBJECT

protected:
	QVBoxLayout * m_pVbox;
	QPushButton* m_pBtn;
	QListWidget* m_pListWidget;

public:
	BtnListWidget(QWidget *parent = 0);
	~BtnListWidget();
};

#endif
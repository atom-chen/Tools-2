#ifndef __MyScrollAreaWidget_H
#define __MyScrollAreaWidget_H

#include "QtIncAll.h"

class MyScrollAreaWidget : public QScrollArea
{
	Q_OBJECT

protected:
	QVBoxLayout * m_pVbox;
	QPushButton* m_pBtn;
	QListWidget* m_pListWidget;

public:
	MyScrollAreaWidget(QWidget *parent = 0);
	~MyScrollAreaWidget();

protected:
	void test1f();
	void test2f();
	QWidget* createGroupBox(const QString& title, int n);
};

#endif
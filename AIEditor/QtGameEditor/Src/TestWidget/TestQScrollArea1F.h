#ifndef __TestQScrollArea1F_H
#define __TestQScrollArea1F_H

#include "QtIncAll.h"

class TestQScrollArea1F :public QWidget
{
	Q_OBJECT
public:
	TestQScrollArea1F(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~TestQScrollArea1F();
private:
	void createWidget();
	QWidget* createGroupBox(const QString& title, int n);
};

#endif
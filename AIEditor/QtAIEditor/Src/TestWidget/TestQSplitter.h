#ifndef __TestQSplitter_H
#define __TestQSplitter_H

#include "QtIncAll.h"

class TestQSplitter :public QWidget
{
	Q_OBJECT

public:
	TestQSplitter(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~TestQSplitter();

protected:
	void testNoLayout();
	void testLayout();
};

#endif
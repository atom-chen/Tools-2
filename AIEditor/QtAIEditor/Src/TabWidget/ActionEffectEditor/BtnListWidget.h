#ifndef __BtnListWidget_H
#define __BtnListWidget_H

#include "QtIncAll.h"
#include <vector>

class DragDropItemWidget;

class BtnListWidget : public QWidget
{
	Q_OBJECT

protected:
	QPushButton* m_pBtn;
	QListWidget* m_pListWidget;
	std::vector<DragDropItemWidget*> m_itemWidgetVec;

public:
	BtnListWidget(QWidget *parent = 0);
	~BtnListWidget();


protected:
	void test1f();
	void test2f();
};

#endif
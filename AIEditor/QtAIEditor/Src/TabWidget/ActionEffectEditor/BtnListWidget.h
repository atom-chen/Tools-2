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
	int m_curWidth;

public:
	BtnListWidget(QWidget *parent = 0, int width_ = 0);
	~BtnListWidget();
	void changgeSize(int width_);

protected:
	void test1f();
	void test2f();
};

#endif
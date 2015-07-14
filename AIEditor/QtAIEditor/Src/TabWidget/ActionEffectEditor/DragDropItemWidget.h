#ifndef __DragDropItemWidget_H
#define __DragDropItemWidget_H

#include "QtIncAll.h"

class DragDropItemWidget : public QWidget
{
	Q_OBJECT

protected:
	QPushButton* m_pBtn;		// һ����ť

public:
	DragDropItemWidget(QWidget *parent = 0, int width_ = 0);
	~DragDropItemWidget();

	void changgeSize(int width_);
};

#endif
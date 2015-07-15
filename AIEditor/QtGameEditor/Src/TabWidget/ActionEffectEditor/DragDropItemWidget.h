#ifndef __DragDropItemWidget_H
#define __DragDropItemWidget_H

#include "QtIncAll.h"

class DragDropItemWidget : public QWidget
{
	Q_OBJECT

protected:
	QPushButton* m_pBtn;		// Ò»¸ö°´Å¥
	QPoint m_dragStartPosition;

public:
	DragDropItemWidget(QWidget *parent = 0, int width_ = 0);
	~DragDropItemWidget();

	void changgeSize(int width_);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif
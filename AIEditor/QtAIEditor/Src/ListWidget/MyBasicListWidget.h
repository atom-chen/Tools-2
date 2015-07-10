#ifndef __MyBasicListWidget_H
#define __MyBasicListWidget_H

#include "QtIncAll.h"

#include "MyBasicTreeWidgetItemLogicData.h"

/**
 * @brief 主要是显示一个目录下的文件和目录，子目录不显示
 */
class MyBasicListWidget : public QWidget
{
	Q_OBJECT

public:
	QLabel *m_label;
	QListWidget *m_list;

public:
	MyBasicListWidget(QWidget *parent = 0);
	void setViewMode(QListView::ViewMode mode);
	void updateListWidget(QString path);
};

#endif
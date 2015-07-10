#ifndef __MyBasicListWidget_H
#define __MyBasicListWidget_H

#include "QtIncAll.h"

#include "MyBasicTreeWidgetItemLogicData.h"

/**
 * @brief ��Ҫ����ʾһ��Ŀ¼�µ��ļ���Ŀ¼����Ŀ¼����ʾ
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
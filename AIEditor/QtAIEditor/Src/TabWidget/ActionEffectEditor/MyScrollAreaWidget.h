#ifndef __MyScrollAreaWidget_H
#define __MyScrollAreaWidget_H

#include "QtIncAll.h"
#include <vector>

class BtnListWidget;

/**
 @brief QScrollArea 会导致 QDockWidget 窗口内部有一个边框
 */
class MyScrollAreaWidget : public QScrollArea
{
	Q_OBJECT

protected:
	QWidget* m_ScrollAreaWidgetContents;	// 这个窗口必须有，所有的内容都要添加到这个窗口下面，这个是顶层窗口
	std::vector<BtnListWidget*> m_vec;

public:
	MyScrollAreaWidget(QWidget *parent = 0);
	~MyScrollAreaWidget();

protected:
	void test1f();
	void test2f();
	void test3f();
	void test4f();
	QWidget* createGroupBox(const QString& title, int n);
};

#endif
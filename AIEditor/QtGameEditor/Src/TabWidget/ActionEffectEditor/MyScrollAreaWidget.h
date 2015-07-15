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
	int m_leftGap;				// 内部距离左边的间隙
	int m_rightGap;				// 内部距离右边的间隙
	int m_topGap;				// 内部距离顶边的间隙
	int m_bottomGap;			// 内部距离底边的间隙

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
	virtual void resizeEvent(QResizeEvent *evt);		// 窗口改变大小事件
};

#endif
#ifndef __MyScrollAreaWidget_H
#define __MyScrollAreaWidget_H

#include "QtIncAll.h"
#include <vector>

class BtnListWidget;

/**
 @brief QScrollArea �ᵼ�� QDockWidget �����ڲ���һ���߿�
 */
class MyScrollAreaWidget : public QScrollArea
{
	Q_OBJECT

protected:
	int m_leftGap;				// �ڲ�������ߵļ�϶
	int m_rightGap;				// �ڲ������ұߵļ�϶
	int m_topGap;				// �ڲ����붥�ߵļ�϶
	int m_bottomGap;			// �ڲ�����ױߵļ�϶

protected:
	QWidget* m_ScrollAreaWidgetContents;	// ������ڱ����У����е����ݶ�Ҫ��ӵ�����������棬����Ƕ��㴰��
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
	virtual void resizeEvent(QResizeEvent *evt);		// ���ڸı��С�¼�
};

#endif
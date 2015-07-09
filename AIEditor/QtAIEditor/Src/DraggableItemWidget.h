#ifndef __DRAGGABLEITEMWIDGET_H
#define __DRAGGABLEITEMWIDGET_H

#include <QtWidgets/QWidget>
#include "AIEditor.h"

class DraggableItemBase;

namespace Ui
{
	class DraggableItemWidget;
}

class DraggableItemWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DraggableItemWidget(QWidget *parent = 0);
	~DraggableItemWidget();

private:
	Ui::DraggableItemWidget *m_ui;
	DraggableItemBase* m_pDraggableItemBase;

public Q_SLOTS:
	void onClkBtn();

public:
	void setDraggableItemBase(DraggableItemBase* pDraggableItemBase);
};

#endif // DRAGGABLEITEMWIDGET_H
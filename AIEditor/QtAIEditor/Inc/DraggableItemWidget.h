#ifndef __DRAGGABLEITEMWIDGET_H
#define __DRAGGABLEITEMWIDGET_H

#include <QtWidgets/QWidget>
#include "AIEditor.h"

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

public Q_SLOTS:
	void onClkBtn();
};

#endif // DRAGGABLEITEMWIDGET_H
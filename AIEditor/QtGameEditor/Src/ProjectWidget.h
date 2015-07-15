#ifndef __PROJECTWIDGET_H
#define __PROJECTWIDGET_H

#include <QtWidgets/QDockWidget>
#include "GameEditor.h"

class QTreeWidgetItem;

namespace Ui
{
	class ProjectWidget;
}

class ProjectWidget : public QDockWidget
{
	Q_OBJECT

public:
	explicit ProjectWidget(QWidget *parent = 0);
	~ProjectWidget();

private slots:
	void showSelectedImage(QTreeWidgetItem * item, int column); //������ڵ��¼�

private:
	Ui::ProjectWidget *m_ui;
};

#endif // PROJECTWIDGET_H
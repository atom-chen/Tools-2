#ifndef __ExplorerWidget_H
#define __ExplorerWidget_H

#include "QtIncAll.h"
#include "AIEditor.h"

class FileSystemModel;

/**
 *@brief 资源管理器窗口
 */
class ExplorerWidget : public QDockWidget
{
	Q_OBJECT

protected:
	FileSystemModel* m_pModel;
	QHBoxLayout * m_pHbox;
	QTreeView* m_pTreeView;

public:
	explicit ExplorerWidget(QWidget *parent = 0);
	~ExplorerWidget();
};

#endif // LOGWIDGET_H
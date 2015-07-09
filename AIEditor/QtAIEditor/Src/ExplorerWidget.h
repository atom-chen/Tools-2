#ifndef __ExplorerWidget_H
#define __ExplorerWidget_H

#include "QtIncAll.h"
#include "AIEditor.h"

class MyFileSystemModel;
class MyDirModel;

/**
 *@brief ��Դ����������
 */
class ExplorerWidget : public QDockWidget
{
	Q_OBJECT

protected:
	//MyFileSystemModel* m_pModel;
	MyDirModel* m_pModel;
	QHBoxLayout * m_pHbox;
	QTreeView* m_pTreeView;

public:
	explicit ExplorerWidget(QWidget *parent = 0);
	~ExplorerWidget();
};

#endif // LOGWIDGET_H
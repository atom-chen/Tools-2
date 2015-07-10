#ifndef __ExplorerWidget_H
#define __ExplorerWidget_H

#include "QtIncAll.h"
#include "AIEditor.h"

class MyBasicFileSystemModel;
class MyDirModel;
class MyBasicMVCTreeWidget;
class MyBasicListWidget;

/**
 *@brief ��Դ����������
 */
class ExplorerWidget : public QDockWidget
{
	Q_OBJECT

protected:
	MyBasicFileSystemModel* m_pModel;
	QHBoxLayout * m_pHbox;
	MyBasicMVCTreeWidget* m_pTreeWidget;
	MyBasicListWidget* m_pListWidget;			// �б���

public:
	explicit ExplorerWidget(QWidget *parent = 0);
	~ExplorerWidget();

public Q_SLOTS:
	void onTreeViewClick(const QModelIndex & index);
	void onTreeViewDoubleClick(const QModelIndex & index);
	void onListDoubleClick(QListWidgetItem *Item);
};

#endif // LOGWIDGET_H
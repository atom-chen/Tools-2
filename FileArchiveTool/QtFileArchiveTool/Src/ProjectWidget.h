#ifndef __PROJECTWIDGET_H
#define __PROJECTWIDGET_H

#include <QtWidgets>

class FileSystemModel;

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

public Q_SLOTS:
	void on_treeView_customContextMenuRequested(const QPoint& pos);

Q_SIGNALS:
	void onTreeItemSelChange(bool isDir, std::string path);

private:
	Ui::ProjectWidget *m_ui;
	// ע�⣬QDirModel �����°� Qt ���Ѿ�������ʹ���ˡ��ĵ���˵ʹ�� QFileSystemModel ���档���������ߵĺ�������һ�������Ծ�û�жԴ�������޸ġ���QDirModel��ͬ���ǣ�QFileSystemModel�������Լ����߳̽����ļ��е�ɨ�裬��˲��ᷢ����ɨ���ļ��ж����µ����߳��������������⣬���� QDirModel����QFileSystemModel�����model������л��棬�����Ҫ����ˢ�½����ǰ���ṩ��refresh()�����������߻�֪ͨQFileSystemWatcher�ࡣ
	QDirModel *m_pModel;
	//FileSystemModel* m_pModel;
};

#endif // PROJECTWIDGET_H
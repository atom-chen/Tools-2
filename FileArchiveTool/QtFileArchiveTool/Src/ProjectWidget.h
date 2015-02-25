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
	// 注意，QDirModel 在最新版 Qt 中已经不建议使用了。文档中说使用 QFileSystemModel 代替。由于这两者的函数几乎一样，所以就没有对代码进行修改。与QDirModel不同的是，QFileSystemModel会启动自己的线程进行文件夹的扫描，因此不会发生因扫描文件夹而导致的主线程阻塞的现象。另外，无论 QDirModel还是QFileSystemModel都会对model结果进行缓存，如果你要立即刷新结果，前者提供了refresh()函数，而后者会通知QFileSystemWatcher类。
	QDirModel *m_pModel;
	//FileSystemModel* m_pModel;
};

#endif // PROJECTWIDGET_H
#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QToolBar>
#include <QTextEdit>
#include <QString>
#include <QMenuBar>
#include <string>

class LogWidget;
class ProjectWidget;
class CenterTabWidget;
class DragWidget;

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void createMenus();
	void createActions();
	void createToolBars();
	void loadFile(QString fileName);

public slots:
	void slotNewFile();
	void slotOpenFile();
	//void slotSaveFile();

public Q_SLOTS:
	void onTreeItemSelChange(bool isDir, std::string path);
	void showProject();
	void showLog();
	void onProjectVisibilityChanged(bool bVisible);
	void update();

private:
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *viewMenu;
	QMenu *aboutMenu;

	QString fileName;

	QToolBar *fileTool;
	QToolBar *editTool;

	QAction *fileOpenAction;
	QAction *fileNewAction;
	QAction *fileSaveAction;
	QAction *exitAction;
	QAction *copyAction;
	QAction *cutAction;
	QAction *pasteAction;
	QAction *aboutAction;

	QAction *showProjectAction;
	QAction *showLogAction;

	QTextEdit *text;
	QMainWindow* m_pSubMainWin;
	QTimer *m_timer;

private:
	Ui::MainWindow *m_ui;

	ProjectWidget* m_projectWidget;
	CenterTabWidget* m_centerTabWidget;
	LogWidget* m_logWidget;

private:
	void connectAction();
	void createDockWidget();
	void createTimer();

	void insGlobal();

protected:
	void closeEvent(QCloseEvent *event);		// ¹Ø±ÕÊÂ¼þ
};

#endif // MAINWINDOW_H
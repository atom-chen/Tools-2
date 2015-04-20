#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include <QtWidgets>
#include <QtCore>
#include "FileSystemModel.h"
#include "QtFileArchiveToolSys.h"
#include "PakState.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);

	this->setWidget(m_ui->verticalLayoutWidget);	// 调整窗口的父窗口

	m_pModel = new QDirModel;
	//m_pModel = new FileSystemModel;
	m_pModel->setReadOnly(false);
	m_pModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	m_ui->mDirTreeView->setModel(m_pModel);
	//m_ui->mDirTreeView->setRootIndex(m_pModel->index("E:\\"));
	// 检查是否有设置 rootPath
	if (QtFileArchiveToolSysDef->getConfigPtr()->getBrowseRootPath().length())
	{
		m_ui->mDirTreeView->setRootIndex(m_pModel->index(QtFileArchiveToolSysDef->getConfigPtr()->getBrowseRootPath().c_str()));
	}

	m_ui->mDirTreeView->header()->setStretchLastSection(true);
	m_ui->mDirTreeView->header()->setSortIndicator(0, Qt::AscendingOrder);
	m_ui->mDirTreeView->header()->setSortIndicatorShown(true);

	QModelIndex index = m_pModel->index(QDir::currentPath());
	m_ui->mDirTreeView->expand(index);
	m_ui->mDirTreeView->scrollTo(index);
	m_ui->mDirTreeView->resizeColumnToContents(0);

	//设置 QTreeView 可以使用右键菜单
	m_ui->mDirTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(m_ui->mDirTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_treeView_customContextMenuRequested(QPoint)));

	createAction();
	createToolBar();
}

ProjectWidget::~ProjectWidget()
{

}

void ProjectWidget::on_treeView_customContextMenuRequested(const QPoint& pos)
{
	//qDebug() << "on_treeView_customContextMenuRequested";
	QModelIndex index = m_ui->mDirTreeView->currentIndex();
	if (!index.isValid()) 
	{
		return;
	}

	QFileInfo fileInfo = m_pModel->fileInfo(index);
	QMenu* menu = nullptr;
	menu = new QMenu(this);

	QAction* ac = nullptr;

	QString fileName = m_ui->mDirTreeView->model()->data(index).toString();
	m_pPath = QtFileArchiveToolSysDef->getCharsetConvPtr()->Utf8ToLocalStr(fileInfo.absoluteFilePath().toUtf8().data());

	if (fileInfo.isDir())
	{
		//menu->addAction(QString(tr("%1-Import").arg(fileName)), this, SLOT(slotTest()));
		//menu->addAction(QString(tr("%1-Export").arg(fileName)), this, SLOT(slotTest()));

		//ac = new QAction(QStringLiteral("构建"), this);
		//menu->addAction(ac);

		//QMenu* itemChildMenu = new QMenu(menu);
		//itemChildMenu->setTitle(QStringLiteral("用…打开"));
		//ac = new QAction(QStringLiteral("C++编辑器"), this);
		//itemChildMenu->addAction(ac);

		//menu->addAction(itemChildMenu->menuAction());

		ac = new QAction(QStringLiteral("Archive Dir"), this);
		menu->addAction(ac);
		QObject::connect(ac, SIGNAL(triggered()), this, SLOT(archiveDir()));

		//ac = new QAction(QStringLiteral("Archive Sub Dir"), this);
		//menu->addAction(ac);
		//QObject::connect(ac, SIGNAL(triggered()), this, SLOT(archiveSubDir()));
	}
	else if (fileInfo.isFile())
	{
		ac = new QAction(QStringLiteral("UNArchive Dir"), this);
		menu->addAction(ac);
		QObject::connect(ac, SIGNAL(triggered()), this, SLOT(unArchiveFile()));
	}
	else
	{
		ac = new QAction(QStringLiteral("No Operator"), this);
		menu->addAction(ac);
	}

	menu->exec(QCursor::pos());

	emit onTreeItemSelChange(true, "nihao");
}

void ProjectWidget::archiveDir()
{
	//QtFileArchiveToolSysDef->getArchiveParamPtr()->setArchiveMode(eArchiveMode_Dir);
	archive();
}

void ProjectWidget::archiveSubDir()
{
	//QtFileArchiveToolSysDef->getArchiveParamPtr()->setArchiveMode(eArchiveMode_SubDir);
	archive();
}

void ProjectWidget::archive()
{
	if (QtFileArchiveToolSysDef->getPakStatePtr()->isEqualState(ePS_PAKING))
	{
		QtFileArchiveToolSysDef->getLogSysPtr()->log("当前正在打包中\n");
		return;
	}
	QtFileArchiveToolSysDef->getArchiveParamPtr()->setArchiveDir(m_pPath.c_str());
	std::string filePath = QtFileArchiveToolSysDef->getUtilPtr()->getFullPathNoFileName(m_pPath.c_str());
	filePath += "/";
	filePath += QtFileArchiveToolSysDef->getUtilPtr()->getLastPathName(m_pPath.c_str());
	filePath += PAKEXT;
	QtFileArchiveToolSysDef->getArchiveParamPtr()->setArchiveFilePath(filePath.c_str());
	QtFileArchiveToolSysDef->getArchiveDataPtr()->ArchiveDir();
}

void ProjectWidget::unArchiveFile()
{
	QtFileArchiveToolSysDef->getUnArchiveParamPtr()->setUnArchiveFilePath(m_pPath.c_str());
	QtFileArchiveToolSysDef->getUnArchiveParamPtr()->setUnArchiveOutDir(QtFileArchiveToolSysDef->getUtilPtr()->getFullPathNoExtName(m_pPath.c_str()));
	QtFileArchiveToolSysDef->getArchiveDataPtr()->unArchiveFile();
}

void ProjectWidget::createToolBar()
{
	QToolBar *projectToolBar = new QToolBar(m_ui->verticalLayoutWidget);
	projectToolBar->setObjectName("projectToolBar");
	projectToolBar->setIconSize(QSize(20, 20));
	projectToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	projectToolBar->addAction(m_actRefresh);

	m_ui->verticalLayout->addWidget(projectToolBar, 1);
}

void ProjectWidget::createAction()
{
	m_actRefresh = new QAction(tr("Refresh"), this);
	m_actRefresh->setStatusTip(tr("Refresh List"));
	m_actRefresh->setIcon(QIcon(":/Icons/new.png"));
	connect(m_actRefresh, SIGNAL(triggered()), this, SLOT(refreshList()));
}

void ProjectWidget::refreshList()
{
	m_pModel->refresh();
}
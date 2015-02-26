#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include <QtWidgets>
#include <QtCore>
#include "FileSystemModel.h"
#include "QtFileArchiveToolSys.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);

	this->setWidget(m_ui->verticalLayoutWidget);

	m_pModel = new QDirModel;
	//m_pModel = new FileSystemModel;
	m_pModel->setReadOnly(false);
	m_pModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	m_ui->mDirTreeView->setModel(m_pModel);
	//m_ui->mDirTreeView->setRootIndex(m_pModel->index("E:\\"));
	// ����Ƿ������� rootPath
	if (QtFileArchiveToolSysDef->getConfigPtr()->getRootPath().length())
	{
		m_ui->mDirTreeView->setRootIndex(m_pModel->index(QtFileArchiveToolSysDef->getConfigPtr()->getRootPath().c_str()));
	}

	m_ui->mDirTreeView->header()->setStretchLastSection(true);
	m_ui->mDirTreeView->header()->setSortIndicator(0, Qt::AscendingOrder);
	m_ui->mDirTreeView->header()->setSortIndicatorShown(true);

	QModelIndex index = m_pModel->index(QDir::currentPath());
	m_ui->mDirTreeView->expand(index);
	m_ui->mDirTreeView->scrollTo(index);
	m_ui->mDirTreeView->resizeColumnToContents(0);

	//���� QTreeView ����ʹ���Ҽ��˵�
	m_ui->mDirTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(m_ui->mDirTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_treeView_customContextMenuRequested(QPoint)));
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
	m_pPath = QtFileArchiveToolSysDef->getCharsetConvPtr()->UTF8ToGBKStr(fileInfo.absoluteFilePath().toUtf8().data());

	if (fileInfo.isDir())
	{
		//menu->addAction(QString(tr("%1-Import").arg(fileName)), this, SLOT(slotTest()));
		//menu->addAction(QString(tr("%1-Export").arg(fileName)), this, SLOT(slotTest()));

		//ac = new QAction(QStringLiteral("����"), this);
		//menu->addAction(ac);

		//QMenu* itemChildMenu = new QMenu(menu);
		//itemChildMenu->setTitle(QStringLiteral("�á���"));
		//ac = new QAction(QStringLiteral("C++�༭��"), this);
		//itemChildMenu->addAction(ac);

		//menu->addAction(itemChildMenu->menuAction());

		ac = new QAction(QStringLiteral("Archive Dir"), this);
		menu->addAction(ac);
		QObject::connect(ac, SIGNAL(triggered()), this, SLOT(archiveDir()));
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
	QtFileArchiveToolSysDef->getArchiveDataPtr()->ArchiveDir(m_pPath.c_str());
}

void ProjectWidget::unArchiveFile()
{
	QtFileArchiveToolSysDef->getArchiveDataPtr()->unArchiveFile(m_pPath.c_str());
}
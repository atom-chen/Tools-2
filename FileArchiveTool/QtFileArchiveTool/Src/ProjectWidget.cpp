#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include <QtWidgets>
#include <QtCore>

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);

	this->setWidget(m_ui->verticalLayoutWidget);

	m_pModel = new QDirModel;
	m_pModel->setReadOnly(false);
	m_pModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	m_ui->mDirTreeView->setModel(m_pModel);
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

	if (fileInfo.isDir())
	{
		QString fileName = m_ui->mDirTreeView->model()->data(index).toString();
		QMenu* menu = new QMenu(this);
		menu->addAction(QString(tr("%1-Import").arg(fileName)), this, SLOT(slotTest()));
		menu->addAction(QString(tr("%1-Export").arg(fileName)), this, SLOT(slotTest()));

		QAction* ac = nullptr;
		ac = new QAction(QStringLiteral("构建"), this);
		menu->addAction(ac);

		QMenu* itemChildMenu = new QMenu(menu);
		itemChildMenu->setTitle(QStringLiteral("用…打开"));
		ac = new QAction(QStringLiteral("C++编辑器"), this);
		itemChildMenu->addAction(ac);

		menu->addAction(itemChildMenu->menuAction());

		menu->exec(QCursor::pos());
	}

	emit onTreeItemSelChange(true, "nihao");
}
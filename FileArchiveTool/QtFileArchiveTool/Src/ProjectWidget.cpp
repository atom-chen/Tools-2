#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include <QtWidgets>

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);

	this->setWidget(m_ui->verticalLayoutWidget);

	QDirModel* model = new QDirModel;
	model->setReadOnly(false);
	model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	m_ui->mDirTreeView->setModel(model);
	m_ui->mDirTreeView->header()->setStretchLastSection(true);
	m_ui->mDirTreeView->header()->setSortIndicator(0, Qt::AscendingOrder);
	m_ui->mDirTreeView->header()->setSortIndicatorShown(true);

	QModelIndex index = model->index(QDir::currentPath());
	m_ui->mDirTreeView->expand(index);
	m_ui->mDirTreeView->scrollTo(index);
	m_ui->mDirTreeView->resizeColumnToContents(0);
}

ProjectWidget::~ProjectWidget()
{

}
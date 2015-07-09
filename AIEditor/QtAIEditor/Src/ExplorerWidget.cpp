#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"

ExplorerWidget::ExplorerWidget(QWidget *parent)
	: QDockWidget(parent, 0)
{
	this->setObjectName(QStringLiteral("ExplorerWidget"));
	this->setWindowTitle(QStringLiteral("ExplorerWidget"));		// ����ͣ�����ڵı��⣬����û�б�����ʾ

	// Layout ����ռλ����
	QWidget* _HLayoutWidget = new QWidget/*(this)*/;	// ������� setWidget ���ô���
	// this->setWidget(_HLayoutWidget);

	// ���ô��ڲ���
	m_pHbox = new QHBoxLayout(_HLayoutWidget);	// ���츳ֵ���� setLayout ��ֵ
	//this->setLayout(m_pHbox);
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	// Ŀ¼����
	m_pModel = new MyBasicFileSystemModel;
	//m_pModel = new MyDirModel;

	m_pTreeView = new QTreeView(_HLayoutWidget);
	m_pHbox->addWidget(m_pTreeView);
	m_pTreeView->setModel(m_pModel);
	m_pTreeView->setRootIndex(m_pModel->index("E:/Self"));	// ����� QFileSystemModel ģ�ͣ����� QTreeView::setRootIndex û��Ч������Ҫ��ͬʱ���� QFileSystemModel::setRootPath �� QTreeView::setRootIndex ���С� QDirModel ֻ��Ҫ���� QTreeView::setRootIndex �����ˡ�

	m_pTreeView->header()->setStretchLastSection(true);
	m_pTreeView->header()->setSortIndicator(0, Qt::AscendingOrder);
	m_pTreeView->header()->setSortIndicatorShown(true);

	// ����� QFileSystemModel �����û���������δ��룬�ǲ��ܿ����κ����ݵġ����� QDirModel û������Ĵ���Ҳ���Կ�������
	{
		QModelIndex index = m_pModel->index(QDir::currentPath());
		m_pTreeView->expand(index);
		m_pTreeView->scrollTo(index);
		m_pTreeView->resizeColumnToContents(0);
	}

	// �б���
	m_pListWidget = new QListWidget(_HLayoutWidget);
	m_pHbox->addWidget(m_pListWidget);

	this->setWidget(_HLayoutWidget);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

ExplorerWidget::~ExplorerWidget()
{

}
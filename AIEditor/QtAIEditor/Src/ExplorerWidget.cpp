#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"
#include "MyBasicMVCTreeWidget.h"
#include "MyBasicListWidget.h"
#include "MyBasicTreeView.h"
#include "QtAIEditorSys.h"
#include "TabWidgetMgr.h"
#include "MyBasicListWidgetItemData.h"
#include "MyBasicListWidgetItem.h"

ExplorerWidget::ExplorerWidget(QWidget *parent)
	: QDockWidget(parent, 0)
{
	this->setObjectName(QStringLiteral("ExplorerWidget"));
	this->setWindowTitle(QStringLiteral("ExplorerWidget"));		// ����ͣ�����ڵı��⣬����û�б�����ʾ

	// Layout ����ռλ����
	QWidget* _HLayoutWidget = new QWidget/*(this)*/;	// ������� setWidget ���ô���

	// ���ô��ڲ���
	m_pHbox = new QHBoxLayout/*(_HLayoutWidget)*/;	// ���츳ֵ���� setLayout ��ֵ
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	// Ŀ¼����
	m_pTreeWidget = new MyBasicMVCTreeWidget(_HLayoutWidget);
	m_pTreeWidget->add2Layout(m_pHbox);
	// ����¼�������
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(clicked(const QModelIndex)), this, SLOT(onTreeViewClick(const QModelIndex)));
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onTreeViewDoubleClick(const QModelIndex)));

	// �б���
	m_pListWidget = new MyBasicListWidget;
	//m_pListWidget->resize(400, 200);
	//m_pListWidget->show();
	m_pHbox->addWidget(m_pListWidget);
	// ��Ӽ����¼�
	QObject::connect(m_pListWidget->getListWidgetPtr(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListDoubleClick(QListWidgetItem *)));

	_HLayoutWidget->setLayout(m_pHbox);
	this->setWidget(_HLayoutWidget);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

ExplorerWidget::~ExplorerWidget()
{

}

// ��������Դ��������
void ExplorerWidget::onTreeViewClick(const QModelIndex & index)
{
	QFileInfo fileInfo = m_pTreeWidget->fileInfo(index);
	m_pListWidget->updateListWidget(fileInfo.absoluteFilePath());
}

void ExplorerWidget::onTreeViewDoubleClick(const QModelIndex & index)
{
	// QAbstractItemModel* m = (QAbstractItemModel*)index.model();
	QFileInfo fileInfo = m_pTreeWidget->fileInfo(index);
}

// ˫�� List ��
void ExplorerWidget::onListDoubleClick(QListWidgetItem *Item)
{
	// test
	//MyBasicListWidgetItemData itemData;
	//QVariant userData = Item->data(Qt::UserRole);
	//if (userData.canConvert<MyBasicListWidgetItemData>())
	//{
	//	itemData = userData.value<MyBasicListWidgetItemData>();
	//}
	MyBasicListWidgetItem* pItem = (MyBasicListWidgetItem*)Item;
	MyBasicListWidgetItemData* pItemData = pItem->getItemData();
	if (pItemData->getBFile())	// ֻ�����ļ���ʱ��Ż�༭
	{
		g_pTabWidgetMgr->openOneActionEffectEditor(pItemData->getFullPath());
	}
}
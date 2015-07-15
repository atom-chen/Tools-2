#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"
#include "MyBasicMVCTreeWidget.h"
#include "MyBasicListWidget.h"
#include "MyBasicTreeView.h"
#include "QtGameEditorSys.h"
#include "TabWidgetMgr.h"
#include "MyBasicListWidgetItemData.h"
#include "MyBasicListWidgetItem.h"
#include "TestQSplitter.h"

ExplorerWidget::ExplorerWidget(QWidget *parent)
	: QDockWidget(parent, 0)
{
	this->setObjectName(QStringLiteral("ExplorerWidget"));
	this->setWindowTitle(QStringLiteral("ExplorerWidget"));		// ����ͣ�����ڵı��⣬����û�б�����ʾ

	//layoutSplit();
	//splitterSplitNoLayout();
	//splitterSplitWithLayoutNoParent();
	splitterSplitWithLayoutWithParent();
	//testSplitterNoLayout();
	//testSplitterWithLayout();
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

// ʹ�� QHBoxLayout ���Ѵ��ڣ������ķ��Ѵ����ǲ����϶���
void ExplorerWidget::layoutSplit()
{
	// Layout ����ռλ����
	QWidget* _dockWidgetContents = new QWidget/*(this)*/;	// ������� setWidget ���ô���

	// ���ô��ڲ���
	m_pHbox = new QHBoxLayout/*(_HLayoutWidget)*/;	// ���츳ֵ���� setLayout ��ֵ
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	// Ŀ¼����
	m_pTreeWidget = new MyBasicMVCTreeWidget(_dockWidgetContents);
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

	_dockWidgetContents->setLayout(m_pHbox);
	this->setWidget(_dockWidgetContents);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

// ʹ�� QSplitter �ָ�ڣ����ڿ����϶�������С
void ExplorerWidget::splitterSplitNoLayout()
{
	// Layout ����ռλ����
	QWidget* _dockWidgetContents = new QWidget/*(this)*/;	// ������� setWidget ���ô���

	// QSplitter ����
	m_mainSplitter = new QSplitter(Qt::Horizontal);
	m_mainSplitter->setObjectName(QStringLiteral("ExplorerWidgetQSplitter"));
	m_mainSplitter->setHandleWidth(10);
	m_mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //���÷ֽ��ߵ���ʽ
	m_mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//m_mainSplitter->setOpaqueResize(false);			// �����϶�ʱ�Ƿ�ʵʱ����
	//m_mainSplitter->setStretchFactor(0, 1);			// �趨�������ؼ�
	//m_mainSplitter->setStretchFactor(1, 1);			// �趨�������ؼ�

	// Ŀ¼����
	m_pTreeWidget = new MyBasicMVCTreeWidget(_dockWidgetContents);
	m_pTreeWidget->add2Splitter(m_mainSplitter);
	// ����¼�������
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(clicked(const QModelIndex)), this, SLOT(onTreeViewClick(const QModelIndex)));
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onTreeViewDoubleClick(const QModelIndex)));

	// �б���
	m_pListWidget = new MyBasicListWidget;
	m_mainSplitter->addWidget(m_pListWidget);
	// ��Ӽ����¼�
	QObject::connect(m_pListWidget->getListWidgetPtr(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListDoubleClick(QListWidgetItem *)));

	this->setWidget(_dockWidgetContents);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

void ExplorerWidget::splitterSplitWithLayoutNoParent()
{
	// Layout ����ռλ����
	QWidget* _dockWidgetContents = new QWidget/*(this)*/;	// ������� setWidget ���ô���

	// ���ô��ڲ���
	m_pHbox = new QHBoxLayout/*(_HLayoutWidget)*/;	// ���츳ֵ���� setLayout ��ֵ
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	m_pHSplitterbox = new QHBoxLayout;
	m_pHSplitterbox->setObjectName(QStringLiteral("ExplorerWidgetSplitterHbox"));
	m_pHSplitterbox->setContentsMargins(0, 0, 0, 0);

	// QSplitter ����
	m_mainSplitter = new QSplitter(Qt::Horizontal, _dockWidgetContents);
	m_mainSplitter->setObjectName(QStringLiteral("ExplorerWidgetQSplitter"));
	m_mainSplitter->setHandleWidth(10);
	m_mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //���÷ֽ��ߵ���ʽ
	m_mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//m_mainSplitter->setOpaqueResize(false);			// �����϶�ʱ�Ƿ�ʵʱ����
	//m_mainSplitter->setStretchFactor(0, 1);			// �趨�������ؼ�
	//m_mainSplitter->setStretchFactor(1, 1);			// �趨�������ؼ�

	// Ŀ¼����
	m_pTreeWidget = new MyBasicMVCTreeWidget();
	m_pTreeWidget->add2Splitter(m_mainSplitter);
	// ����¼�������
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(clicked(const QModelIndex)), this, SLOT(onTreeViewClick(const QModelIndex)));
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onTreeViewDoubleClick(const QModelIndex)));

	// �б���
	m_pListWidget = new MyBasicListWidget;
	m_mainSplitter->addWidget(m_pListWidget);
	// ��Ӽ����¼�
	QObject::connect(m_pListWidget->getListWidgetPtr(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListDoubleClick(QListWidgetItem *)));

	m_pHSplitterbox->addWidget(m_mainSplitter);
	m_mainSplitter->setLayout(m_pHSplitterbox);		// ִ�е�����ط������������� QSplitter ���Ѵ��ڲ������ QHBoxLayout ����

	_dockWidgetContents->setLayout(m_pHbox);
	this->setWidget(_dockWidgetContents);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

void ExplorerWidget::splitterSplitWithLayoutWithParent()
{
	// Layout ����ռλ����
	QWidget* _dockWidgetContents = new QWidget/*(this)*/;	// ������� setWidget ���ô���

	// ���ô��ڲ���
	m_pHbox = new QHBoxLayout/*(_HLayoutWidget)*/;	// ���츳ֵ���� setLayout ��ֵ
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	m_pHSplitterbox = new QHBoxLayout;
	m_pHSplitterbox->setObjectName(QStringLiteral("ExplorerWidgetSplitterHbox"));
	m_pHSplitterbox->setContentsMargins(0, 0, 0, 0);

	m_splitterParent = new QWidget(_dockWidgetContents);

	// QSplitter ����
	m_mainSplitter = new QSplitter(Qt::Horizontal, m_splitterParent);
	m_mainSplitter->setObjectName(QStringLiteral("ExplorerWidgetQSplitter"));
	//m_mainSplitter->setHandleWidth(10);
	//m_mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //���÷ֽ��ߵ���ʽ
	m_mainSplitter->setStyleSheet("QSplitter::handle { background-color: lightgray }"); //���÷ֽ��ߵ���ʽ
	m_mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_mainSplitter->setOpaqueResize(false);			// �����϶�ʱ�Ƿ�ʵʱ����
	m_mainSplitter->setStretchFactor(0, 1);			// �趨�������ؼ�
	m_mainSplitter->setStretchFactor(1, 1);			// �趨�������ؼ�
	//m_mainSplitter->setDisabled(true);				// Disable the Middle Line, it can't adjust. 

	// Ŀ¼����
	m_pTreeWidget = new MyBasicMVCTreeWidget;
	m_pTreeWidget->add2Splitter(m_mainSplitter);
	// ����¼�������
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(clicked(const QModelIndex)), this, SLOT(onTreeViewClick(const QModelIndex)));
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onTreeViewDoubleClick(const QModelIndex)));

	// �б���
	m_pListWidget = new MyBasicListWidget;
	m_mainSplitter->addWidget(m_pListWidget);
	// ��Ӽ����¼�
	QObject::connect(m_pListWidget->getListWidgetPtr(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListDoubleClick(QListWidgetItem *)));

	m_pHSplitterbox->addWidget(m_mainSplitter);
	m_splitterParent->setLayout(m_pHSplitterbox);

	m_pHbox->addWidget(m_splitterParent);

	_dockWidgetContents->setLayout(m_pHbox);
	this->setWidget(_dockWidgetContents);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

void ExplorerWidget::testSplitterNoLayout()
{
	QWidget* _dockWidgetContents = new QWidget;					// ���ͣ�����ڶ�λ���� QDockWidget �߽��λ�ã�����ֱ�Ӵ�ԭ�㿪ʼ
	TestQSplitter* pTestQSplitter = new TestQSplitter(_dockWidgetContents);
	this->setWidget(_dockWidgetContents);
}

void ExplorerWidget::testSplitterWithLayout()
{
	QWidget* _dockWidgetContents = new QWidget;					// ���ͣ�����ڶ�λ���� QDockWidget �߽��λ�ã�����ֱ�Ӵ�ԭ�㿪ʼ
	m_pHbox = new QHBoxLayout;
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	TestQSplitter* pTestQSplitter = new TestQSplitter(_dockWidgetContents);
	m_pHbox->addWidget(pTestQSplitter);

	_dockWidgetContents->setLayout(m_pHbox);
	this->setWidget(_dockWidgetContents);
}
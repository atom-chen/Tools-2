#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include "MyBasicTreeWidgetItemData.h"
#include "MyBasicTreeWidgetItem.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);
	m_ui->dockWidgetContents->setLayout(m_ui->verticalLayout);	// QDockWidget ������ QtDesigner �ж������� *.ui �����ĸ�ʽ������ dockWidgetContents ����û�м� Layout ���� verticalLayout �Ĳ��ִ����� verticalLayoutWidget ������ dockWidgetContents ���ܱ����֣�����������߸� dockWidgetContents ���һ�� QVBoxLayout ������ֱ�ӽ� verticalLayout ��ӵ� dockWidgetContents ��������ϣ����ǲ�Ҫ�� *.ui �ļ��н� verticalLayoutWidget ȥ���������� QtDesigner �оͲ��ܲ鿴 QVBoxLayout ���������

	// �������ؼ�����
	m_ui->treeWidget->setColumnCount(1); //��������
	m_ui->treeWidget->setHeaderLabel(QStringLiteral("�����������")); //����ͷ�ı���
	connect(m_ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(showSelectedImage(QTreeWidgetItem*, int)));

	MyBasicTreeWidgetItem *imageItem1 = new MyBasicTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("ͼ��1")));
	MyBasicTreeWidgetItemData* itemWidget = new MyBasicTreeWidgetItemData;
	itemWidget->m_self = itemWidget;
	imageItem1->setData(0, Qt::UserRole, itemWidget->m_value);
	imageItem1->setIcon(0, QIcon("xxx.png"));
	MyBasicTreeWidgetItem *imageItem1_1 = new MyBasicTreeWidgetItem(imageItem1, QStringList(QStringLiteral("Band1"))); //�ӽڵ�1
	imageItem1->addChild(imageItem1_1); //����ӽڵ�

	MyBasicTreeWidgetItem *imageItem2 = new MyBasicTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("ͼ��2")));
	MyBasicTreeWidgetItem *imageItem2_1 = new MyBasicTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band1"))); //�ӽڵ�1
	MyBasicTreeWidgetItem *imageItem2_2 = new MyBasicTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band2"))); //�ӽڵ�2
	imageItem2->addChild(imageItem2_1);  //����ӽڵ�
	imageItem2->addChild(imageItem2_2);

	m_ui->treeWidget->expandAll(); //���ȫ��չ��
}

ProjectWidget::~ProjectWidget()
{

}

void ProjectWidget::showSelectedImage(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem *parent = item->parent();
	if (nullptr == parent) //ע�⣺�������û�и��ڵ�ģ�˫����Щ��ʱע��(����)
	{
		return;
	}
	int col = parent->indexOfChild(item); //item�ڸ����еĽڵ��к�(��0��ʼ)

	if (0 == col)
	{
		//ִ�ж�Ӧ����
	}
	if (1 == col)
	{
		//ִ�ж�Ӧ����
	}

	QVariant userData = item->data(0, Qt::UserRole);
	MyBasicTreeWidgetItemData ret = userData.value<MyBasicTreeWidgetItemData>();
	//ret.delSelf();
}
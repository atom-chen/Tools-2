#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include "ProjectWidgetItemBase.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);
	// �������ؼ�����
	m_ui->treeWidget->setColumnCount(1); //��������
	m_ui->treeWidget->setHeaderLabel(QStringLiteral("�����������")); //����ͷ�ı���
	connect(m_ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(showSelectedImage(QTreeWidgetItem*, int)));

	QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("ͼ��1")));
	ProjectWidgetItemBase* itemWidget = new ProjectWidgetItemBase;
	itemWidget->m_self = itemWidget;
	imageItem1->setData(0, Qt::UserRole, itemWidget->m_value);
	imageItem1->setIcon(0, QIcon("xxx.png"));
	QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QStringLiteral("Band1"))); //�ӽڵ�1
	imageItem1->addChild(imageItem1_1); //����ӽڵ�

	QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("ͼ��2")));
	QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band1"))); //�ӽڵ�1
	QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band2"))); //�ӽڵ�2
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
	ProjectWidgetItemBase ret = userData.value<ProjectWidgetItemBase>();
	//ret.delSelf();
}
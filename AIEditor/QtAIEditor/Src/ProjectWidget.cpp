#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);
	// �������ؼ�����
	m_ui->treeWidget->setColumnCount(1); //��������
	m_ui->treeWidget->setHeaderLabel(QStringLiteral("�����������")); //����ͷ�ı���

	QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("ͼ��1")));
	//imageItem1->setData(0, Qt::UserRole);
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
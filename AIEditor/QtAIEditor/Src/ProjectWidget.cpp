#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);
	// 设置树控件属性
	m_ui->treeWidget->setColumnCount(1); //设置列数
	m_ui->treeWidget->setHeaderLabel(QStringLiteral("解决方案窗口")); //设置头的标题

	QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("图像1")));
	//imageItem1->setData(0, Qt::UserRole);
	imageItem1->setIcon(0, QIcon("xxx.png"));
	QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QStringLiteral("Band1"))); //子节点1
	imageItem1->addChild(imageItem1_1); //添加子节点

	QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("图像2")));
	QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band1"))); //子节点1
	QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band2"))); //子节点2
	imageItem2->addChild(imageItem2_1);  //添加子节点
	imageItem2->addChild(imageItem2_2);

	m_ui->treeWidget->expandAll(); //结点全部展开
}

ProjectWidget::~ProjectWidget()
{

}
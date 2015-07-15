#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include "MyBasicTreeWidgetItemData.h"
#include "MyBasicTreeWidgetItem.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::ProjectWidget)
{
	m_ui->setupUi(this);
	m_ui->dockWidgetContents->setLayout(m_ui->verticalLayout);	// QDockWidget 窗口在 QtDesigner 中都会生成 *.ui 这样的格式，顶层 dockWidgetContents 窗口没有加 Layout ，而 verticalLayout 的布局窗口是 verticalLayoutWidget ，导致 dockWidgetContents 不能被布局，解决方法或者给 dockWidgetContents 添加一个 QVBoxLayout ，或者直接将 verticalLayout 添加到 dockWidgetContents 这个窗口上，但是不要从 *.ui 文件中将 verticalLayoutWidget 去掉，否则在 QtDesigner 中就不能查看 QVBoxLayout 这个布局了

	// 设置树控件属性
	m_ui->treeWidget->setColumnCount(1); //设置列数
	m_ui->treeWidget->setHeaderLabel(QStringLiteral("解决方案窗口")); //设置头的标题
	connect(m_ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(showSelectedImage(QTreeWidgetItem*, int)));

	MyBasicTreeWidgetItem *imageItem1 = new MyBasicTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("图像1")));
	MyBasicTreeWidgetItemData* itemWidget = new MyBasicTreeWidgetItemData;
	itemWidget->m_self = itemWidget;
	imageItem1->setData(0, Qt::UserRole, itemWidget->m_value);
	imageItem1->setIcon(0, QIcon("xxx.png"));
	MyBasicTreeWidgetItem *imageItem1_1 = new MyBasicTreeWidgetItem(imageItem1, QStringList(QStringLiteral("Band1"))); //子节点1
	imageItem1->addChild(imageItem1_1); //添加子节点

	MyBasicTreeWidgetItem *imageItem2 = new MyBasicTreeWidgetItem(m_ui->treeWidget, QStringList(QStringLiteral("图像2")));
	MyBasicTreeWidgetItem *imageItem2_1 = new MyBasicTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band1"))); //子节点1
	MyBasicTreeWidgetItem *imageItem2_2 = new MyBasicTreeWidgetItem(imageItem2, QStringList(QStringLiteral("Band2"))); //子节点2
	imageItem2->addChild(imageItem2_1);  //添加子节点
	imageItem2->addChild(imageItem2_2);

	m_ui->treeWidget->expandAll(); //结点全部展开
}

ProjectWidget::~ProjectWidget()
{

}

void ProjectWidget::showSelectedImage(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem *parent = item->parent();
	if (nullptr == parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
	{
		return;
	}
	int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

	if (0 == col)
	{
		//执行对应操作
	}
	if (1 == col)
	{
		//执行对应操作
	}

	QVariant userData = item->data(0, Qt::UserRole);
	MyBasicTreeWidgetItemData ret = userData.value<MyBasicTreeWidgetItemData>();
	//ret.delSelf();
}
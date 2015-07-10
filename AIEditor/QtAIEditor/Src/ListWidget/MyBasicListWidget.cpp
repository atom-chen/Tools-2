#include "MyBasicListWidget.h"
#include "MyBasicListWidgetItem.h"

MyBasicListWidget::MyBasicListWidget(QWidget *parent)
	: QWidget(parent)
{
	m_label = new QLabel;
	m_label->setFixedWidth(70);
	m_label->setText(QStringLiteral("测试列表"));
	m_list = new QListWidget;
	m_list->addItem(new MyBasicListWidgetItem(QIcon(":/images/line.PNG"), tr("Line")));
	m_list->addItem(new MyBasicListWidgetItem(QIcon(":/images/rect.PNG"), tr("Rectangle")));
	m_list->addItem(new MyBasicListWidgetItem(QIcon(":/images/oval.PNG"), tr("Oval")));
	m_list->addItem(new MyBasicListWidgetItem(QIcon(":/images/tri.PNG"), tr("Triangle")));
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(m_label);
	layout->addWidget(m_list);

	setLayout(layout);

	//connect(m_list, SIGNAL(currentTextChanged(QString)), m_label, SLOT(setText(QString)));
}

void MyBasicListWidget::setViewMode(QListView::ViewMode mode)
{
	m_list->setViewMode(QListView::IconMode);
}

void MyBasicListWidget::updateListWidget(QString path)
{
	m_list->clear();

	QDir qDir(path);
	QFileInfoList fileList = qDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);	// 显示所有的，去掉当前目录和父目录(. 和 ..)
	int idx = 0;
	QFileIconProvider icon_provider;
	QIcon icon;
	for (idx = 0; idx < fileList.size(); ++idx)
	{
		if (fileList[idx].isDir())		// 如果是目录
		{
			icon = icon_provider.icon(QFileIconProvider::Folder);
		}
		else					// 如果是文件
		{
			icon = icon_provider.icon(fileList[idx]);
		}
		m_list->addItem(new MyBasicListWidgetItem(icon, fileList[idx].fileName()));
	}
}
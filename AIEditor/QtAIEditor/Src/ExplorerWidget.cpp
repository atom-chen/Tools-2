#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"
#include "MyBasicTreeWidget.h"
#include "MyBasicListWidget.h"

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
	m_pTreeWidget = new MyBasicTreeWidget(_HLayoutWidget);
	m_pTreeWidget->add2Layout(m_pHbox);

	// �б���
	m_pListWidget = new MyBasicListWidget;
	//m_pListWidget->resize(400, 200);
	//m_pListWidget->show();
	m_pHbox->addWidget(m_pListWidget);

	this->setWidget(_HLayoutWidget);	// ���һ��Ҫ�� Layout �ĸ�������ӵ� DockWidget �У��Ż�ˢ��һ�� Layout ��������ˢ��
}

ExplorerWidget::~ExplorerWidget()
{

}
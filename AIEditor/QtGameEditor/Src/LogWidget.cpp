#include "LogWidget.h"
#include "ui_LogWidget.h"

LogWidget::LogWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::LogWidget)
{
	m_ui->setupUi(this);
	m_ui->dockWidgetContents->setLayout(m_ui->verticalLayout);	// QDockWidget ������ QtDesigner �ж������� *.ui �����ĸ�ʽ������ dockWidgetContents ����û�м� Layout ���� verticalLayout �Ĳ��ִ����� verticalLayoutWidget ������ dockWidgetContents ���ܱ����֣�����������߸� dockWidgetContents ���һ�� QVBoxLayout ������ֱ�ӽ� verticalLayout ��ӵ� dockWidgetContents ��������ϣ����ǲ�Ҫ�� *.ui �ļ��н� verticalLayoutWidget ȥ���������� QtDesigner �оͲ��ܲ鿴 QVBoxLayout ���������
}

LogWidget::~LogWidget()
{

}
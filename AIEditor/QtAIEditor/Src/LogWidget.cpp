#include "LogWidget.h"
#include "ui_LogWidget.h"

LogWidget::LogWidget(QWidget *parent)
	: QDockWidget(parent, 0), m_ui(new Ui::LogWidget)
{
	m_ui->setupUi(this);
	m_ui->dockWidgetContents->setLayout(m_ui->verticalLayout);	// QDockWidget 窗口在 QtDesigner 中都会生成 *.ui 这样的格式，顶层 dockWidgetContents 窗口没有加 Layout ，而 verticalLayout 的布局窗口是 verticalLayoutWidget ，导致 dockWidgetContents 不能被布局，解决方法或者给 dockWidgetContents 添加一个 QVBoxLayout ，或者直接将 verticalLayout 添加到 dockWidgetContents 这个窗口上，但是不要从 *.ui 文件中将 verticalLayoutWidget 去掉，否则在 QtDesigner 中就不能查看 QVBoxLayout 这个布局了
}

LogWidget::~LogWidget()
{

}
#include "DragDropItemWidget.h"

DragDropItemWidget::DragDropItemWidget(QWidget *parent, int width_)
	: QWidget(parent)
{
	this->setGeometry(QRect(0, 0, width_, 30));

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QStringLiteral("pushButton"));
	m_pBtn->setGeometry(QRect(0, 0, width_, 30));
}

DragDropItemWidget::~DragDropItemWidget()
{

}

void DragDropItemWidget::changgeSize(int width_)
{
	QRect pRect;
	pRect = m_pBtn->geometry();
	m_pBtn->setGeometry(pRect.x(), pRect.y(), width_, pRect.height());

	pRect = this->geometry();
	this->setGeometry(pRect.x(), pRect.y(), width_, pRect.height());
}

void DragDropItemWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_dragStartPosition = event->pos();
	}
}

void DragDropItemWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (!(event->buttons() & Qt::LeftButton))
	{
		return;
	}
	if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance())
	{
		return;
	}
	QDrag *drag = new QDrag(this);
	QMimeData *mimeData = new QMimeData;
	QString mimeType = QStringLiteral("text/plain");
	QString uniqueId = QStringLiteral("123");
	mimeData->setData(mimeType, uniqueId.toUtf8());
	drag->setMimeData(mimeData);
	Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}
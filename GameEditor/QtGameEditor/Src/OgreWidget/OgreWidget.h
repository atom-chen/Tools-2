#ifndef QTOGRE_OGREWIDGET_H_
#define QTOGRE_OGREWIDGET_H_

#include <OgreCommon.h>
#include <QWidget>

class OgreWidget : public QWidget
{
	Q_OBJECT

public:
	OgreWidget(QWidget* parent=0, Qt::WindowFlags f=0);
	~OgreWidget();

	Ogre::NameValuePairList getWinParams();

protected:
	QPaintEngine *paintEngine() const;
	void paintEvent(QPaintEvent* evt);
	void resizeEvent(QResizeEvent* evt);
};

#endif
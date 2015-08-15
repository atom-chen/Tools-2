#include "OgreWidget.h"

#include "EventHandler.h"

#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreStringConverter.h>
#include <Ogre.h>

#include <QSettings>

#if defined(Q_WS_X11)
#include <QX11Info>
#endif

#include "GameEditorSys.h"
#include "OgreSys.h"

OgreWidget::OgreWidget(QWidget* parent, Qt::WindowFlags f)
	:QWidget(parent, f/* | Qt::MSWindowsOwnDC*/)
{
	//QPalette colourPalette = palette();
	//colourPalette.setColor(QPalette::Active, QPalette::WindowText, Qt::black);
	//colourPalette.setColor(QPalette::Active, QPalette::Window, Qt::black);
	//setPalette(colourPalette);

	// 如果不设置这两行，会导致屏幕闪烁
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	//Accept input focus
	setFocusPolicy(Qt::StrongFocus);
}

OgreWidget::~OgreWidget()
{
}

QPaintEngine *OgreWidget:: paintEngine() const
{
	return 0;
}

void OgreWidget::paintEvent(QPaintEvent* evt)
{
	if (!isVisible())
		return;

	if (this->width() > 0 && this->height() > 0)
	{
		g_pOgreSys->getRoot()->renderOneFrame();
	}
}

void OgreWidget::resizeEvent(QResizeEvent* evt)
{
	g_pOgreSys->getRenderWindow()->resize(width(), height());
}

Ogre::NameValuePairList OgreWidget::getWinParams()
{
	Ogre::NameValuePairList params;

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
	params["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)(this->winId()));
#else
#if QT_VERSION < 0x050000
	const QX11Info info = this->x11Info();
	Ogre::String winHandle;
	winHandle = Ogre::StringConverter::toString((unsigned long)(info.display()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(info.visual()));

	params["externalWindowHandle"] = winHandle;

#elif QT_VERSION >= 0x050100 && defined(Q_WS_X11)
	const QX11Info info = this->x11Info();
	Ogre::String winHandle;
	winHandle = Ogre::StringConverter::toString((unsigned long)(info.display()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned int)(info.appScreen()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));

	params["externalWindowHandle"] = winHandle;
#else // only for the time between Qt 5.0 and Qt 5.1 when QX11Info was not included
	params["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)(this->winId()));
#endif
#endif

#if defined(Q_OS_MAC)
	params["macAPI"] = "cocoa";
	params["macAPICocoaUseNSView"] = "true";
#endif

	return params;
}
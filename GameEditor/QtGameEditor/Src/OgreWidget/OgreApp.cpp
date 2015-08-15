#include "OgreSys.h"

#include "EventHandlingOgreWidget.h"
#include "GameLogic.h"

#include <OgreConfigFile.h>
#include <OgreRenderSystem.h>
#include <OgreRoot.h>

OgreSys::OgreSys()
:mInternalOgreLog(0)
,mInternalOgreLogManager(0)
,mActiveRenderSystem(0)
,mOpenGLRenderSystem(0)
,mDirect3D9RenderSystem(0)
,mRoot(0)
,mFrameCounter(0)
{
	initialiseLogging();

	try
	{
#ifdef QT_DEBUG
		mRoot = new Ogre::Root("plugins_d.cfg");
#else
		mRoot = new Ogre::Root("plugins.cfg");
#endif
		qDebug("Ogre::Root created successfully.");
	}
	catch(Ogre::Exception& e)
	{
		QString error
			(
			"Failed to create the Ogre::Root object. This is a fatal error and the "
			"application will now exit. There are a few known reasons why this can occur:\n\n"
			"    1) Ensure your plugins.cfg has the correct path to the plugins.\n"
			"    2) In plugins.cfg, use unix style directorary serperators. I.e '/' rather than '\\'.\n"
			"    3) If your plugins.cfg is trying to load the Direct3D plugin, make sure you have DirectX installed on your machine.\n\n"
			"The message returned by Ogre was:\n\n"
			);
		error += QString::fromStdString(e.getFullDescription().c_str());

		//Not much else we can do here...
		std::exit(1);
	}

	//Load the render system plugins. We do that here so that we know what
	//render systems are available by the time we show the settings dialog.
	//Note that the render system is not initialised until the user selects one.
	mOpenGLRenderSystem = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	mDirect3D9RenderSystem = mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
	if(!(mOpenGLRenderSystem || mDirect3D9RenderSystem))
	{
	}
}

OgreSys::~OgreSys()
{
	if (mRoot)
	{
        delete mRoot;
		mRoot = 0;
	}
}

bool OgreSys::isOpenGLAvailable(void) const
{
	return mOpenGLRenderSystem != 0;
}

bool OgreSys::isDirect3D9Available(void) const
{
	return mDirect3D9RenderSystem != 0;
}

unsigned int OgreSys::frameCount(void) const
{
	return mFrameCounter;
}

void OgreSys::initialise(void)
{
	initialiseOgre();

	//Set up resource paths. This can't be done until the OgreWidget
	//is initialised, because we need the GPUProgramManager.
	//if(QFile::exists("resources.cfg"))
	{
		loadResourcePathsFromConfigFile("resources.cfg");
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	mGameLogic->initialise();
}

void OgreSys::update(void)
{
	mGameLogic->update();
	++mFrameCounter;
}

void OgreSys::shutdown(void)
{
	mGameLogic->shutdown();
	mInternalOgreLog->removeListener(this);
}

void OgreSys::initialiseLogging(void)
{
	//Redirect Ogre's logging system to our own
	//This has to all be done before creating the Root object.
	mInternalOgreLogManager = new Ogre::LogManager();
	mInternalOgreLog = mInternalOgreLogManager->createLog("Ogre.log", false, true, true);
	mInternalOgreLog->addListener(this);
}

void OgreSys::initialiseOgre(void)
{
	QString renderSystem = "OpenGL Rendering Subsystem";
	if(renderSystem.compare("OpenGL Rendering Subsystem") == 0)
	{
		mActiveRenderSystem = mOpenGLRenderSystem;
	}
	if(renderSystem.compare("Direct3D9 Rendering Subsystem") == 0)
	{
		mActiveRenderSystem = mDirect3D9RenderSystem;
	}

	Ogre::Root::getSingletonPtr()->setRenderSystem(mActiveRenderSystem);

	Ogre::Root::getSingletonPtr()->initialise(false);
}

void OgreSys::loadResourcePathsFromConfigFile(std::string filename)
{
    // Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(filename.c_str());

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
#include "OgreSys.h"

#include <OgreConfigFile.h>
#include <OgreRenderSystem.h>
#include <OgreRoot.h>
#include "OgreHlmsUnlit.h"
#include "OgreHlmsPbs.h"
#include "OgreHlmsManager.h"
#include "Compositor/OgreCompositorManager2.h"
#include "OgreItem.h"
#include <io.h>

BEGIN_NAMESPACE_GAMEEDITOR

OgreSys::OgreSys()
{
	mResourcePath = "";
	mBackgroundColour = Ogre::ColourValue(0.2f, 0.4f, 0.6f);
	mIsInitialised = false;

	initialiseLogging();

	try
	{
#ifdef _DEBUG || DEBUG
		mRoot = new Ogre::Root("plugins_d.cfg");
#else
		mRoot = new Ogre::Root("plugins.cfg");
#endif
	}
	catch(Ogre::Exception& e)
	{
		
	}

	//Load the render system plugins. We do that here so that we know what
	//render systems are available by the time we show the settings dialog.
	//Note that the render system is not initialised until the user selects one.
	mOpenGL3PlusRenderSystem = mRoot->getRenderSystemByName("OpenGL 3+ Rendering Subsystem");
	mDirect3D11RenderSystem = mRoot->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	if (!(mOpenGL3PlusRenderSystem || mDirect3D11RenderSystem))
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
	return mOpenGL3PlusRenderSystem != 0;
}

bool OgreSys::isDirect3D9Available(void) const
{
	return mDirect3D11RenderSystem != 0;
}

unsigned int OgreSys::frameCount(void) const
{
	return mFrameCounter;
}

void OgreSys::initialise(Ogre::NameValuePairList params, int width, int height)
{
	initialiseOgre(params, width, height);

	setupResources();
	loadResources();
	chooseSceneManager();
	createCamera();
	mWorkspace = setupCompositor();
	createScene01();
}

void OgreSys::update(void)
{
	++mFrameCounter;
}

void OgreSys::shutdown(void)
{
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

void OgreSys::initialiseOgre(Ogre::NameValuePairList params, int width, int height)
{
	std::string renderSystem = "Direct3D11 Rendering Subsystem";
	if(renderSystem == "OpenGL 3+ Rendering Subsystem")
	{
		mActiveRenderSystem = mOpenGL3PlusRenderSystem;
	}
	if(renderSystem == "Direct3D11 Rendering Subsystem")
	{
		mActiveRenderSystem = mDirect3D11RenderSystem;
	}

	Ogre::Root::getSingletonPtr()->setRenderSystem(mActiveRenderSystem);

	Ogre::Root::getSingletonPtr()->initialise(false);

	mRenderWindow = g_pOgreSys->getRoot()->createRenderWindow("QtOgreRenderWindow",
		width,
		height,
		false,
		&params);

	mIsInitialised = true;
}

void OgreSys::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage)
{

}

//-----------------------------------------------------------------------------------
void OgreSys::addResourceLocation(const Ogre::String &archName, const Ogre::String &typeName,
	const Ogre::String &secName)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	// OS X does not set the working directory relative to the app,
	// In order to make things portable on OS X we need to provide
	// the loading with it's own bundle path location
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		Ogre::String(macBundlePath() + "/" + archName), typeName, secName);
#else
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		archName, typeName, secName);
#endif
}
//-----------------------------------------------------------------------------------
void OgreSys::setupResources(void)
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcePath + "resources2.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

		if (secName != "Hlms")
		{
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				addResourceLocation(archName, typeName, secName);
			}
		}
	}
}
//-----------------------------------------------------------------------------------
void OgreSys::registerHlms(void)
{
	Ogre::ConfigFile cf;
	cf.load(mResourcePath + "resources2.cfg");

	Ogre::String dataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

	if (dataFolder.empty())
		dataFolder = "./";
	else if (*(dataFolder.end() - 1) != '/')
		dataFolder += "/";

	Ogre::RenderSystem *renderSystem = mRoot->getRenderSystem();

	Ogre::String shaderSyntax = "GLSL";
	if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
		shaderSyntax = "HLSL";

	Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(
		dataFolder + "Hlms/Common/" + shaderSyntax,
		"FileSystem", true);

	Ogre::ArchiveVec library;
	library.push_back(archiveLibrary);

	Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(
		dataFolder + "Hlms/Unlit/" + shaderSyntax,
		"FileSystem", true);

	Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
	Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);

	Ogre::Archive *archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(
		dataFolder + "Hlms/Pbs/" + shaderSyntax,
		"FileSystem", true);
	Ogre::HlmsPbs *hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &library);
	Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);

	if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
	{
		//Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
		//and below to avoid saturating AMD's discard limit (8MB) or
		//saturate the PCIE bus in some low end machines.
		bool supportsNoOverwriteOnTextureBuffers;
		renderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV",
			&supportsNoOverwriteOnTextureBuffers);

		if (!supportsNoOverwriteOnTextureBuffers)
		{
			hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
			hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
		}
	}
}
//-----------------------------------------------------------------------------------
void OgreSys::loadResources(void)
{
	registerHlms();

	// Initialise, parse scripts etc
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-----------------------------------------------------------------------------------
void OgreSys::chooseSceneManager(void)
{
	Ogre::InstancingThreadedCullingMethod threadedCullingMethod =
		Ogre::INSTANCING_CULLING_SINGLETHREAD;
#if OGRE_DEBUG_MODE
	//Debugging multithreaded code is a PITA, disable it.
	const size_t numThreads = 1;
#else
	//getNumLogicalCores() may return 0 if couldn't detect
	const size_t numThreads = std::max<size_t>(1, Ogre::PlatformInformation::getNumLogicalCores());
	//See doxygen documentation regarding culling methods.
	//In some cases you may still want to use single thread.
	//if( numThreads > 1 )
	//	threadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
#endif
	// Create the SceneManager, in this case a generic one
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC,
		numThreads,
		threadedCullingMethod,
		"ExampleSMInstance");

	//mSceneManager->addRenderQueueListener(mOverlaySystem);

	//Set sane defaults for proper shadow mapping
	mSceneManager->setShadowDirectionalLightExtrusionDistance(500.0f);
	mSceneManager->setShadowFarDistance(500.0f);
}
//-----------------------------------------------------------------------------------
void OgreSys::createCamera(void)
{
	mCamera = mSceneManager->createCamera("Main Camera");

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0, 5, 15));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(0.2f);
	mCamera->setFarClipDistance(1000.0f);
	mCamera->setAutoAspectRatio(true);

	//Viewport* pViewport = mRenderWindow->addViewport();
}
//-----------------------------------------------------------------------------------
Ogre::CompositorWorkspace* OgreSys::setupCompositor(void)
{
	Ogre::CompositorManager2 *compositorManager = mRoot->getCompositorManager2();

	const Ogre::IdString workspaceName("Demo Workspace");
	if (!compositorManager->hasWorkspaceDefinition(workspaceName))
	{
		compositorManager->createBasicWorkspaceDef(workspaceName, mBackgroundColour,
			Ogre::IdString());
	}

	return compositorManager->addWorkspace(mSceneManager, mRenderWindow, mCamera,
		workspaceName, true);
}

void OgreSys::setRenderWindow(Ogre::RenderWindow* renderWin)
{
	mRenderWindow = renderWin;
}

void OgreSys::createScene01(void)
{
	Ogre::Item *item = mSceneManager->createItem("aaa.mesh",
		Ogre::ResourceGroupManager::
		AUTODETECT_RESOURCE_GROUP_NAME,
		Ogre::SCENE_DYNAMIC);

	mSceneNode = mSceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->
		createChildSceneNode(Ogre::SCENE_DYNAMIC);

	mSceneNode->attachObject(item);
}

END_NAMESPACE_GAMEEDITOR
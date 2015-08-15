#ifndef QTOGRE_APPLICATION_H_
#define QTOGRE_APPLICATION_H_

#include "GameEditor.h"

#include <Ogre.h>
#include <string>
//#include <WinUser.h>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT OgreSys : public Ogre::LogListener
{
public:
	OgreSys();
	virtual ~OgreSys();

	unsigned int frameCount(void) const;
	void setAutoUpdateInterval(int intervalInMilliseconds);
	void setAutoUpdateEnabled(bool autoUpdateEnabled);

	bool isOpenGLAvailable(void) const;
	bool isDirect3D9Available(void) const;

public:
	void initialise(Ogre::NameValuePairList params, int width, int height);
	void shutdown(void);
	void update(void);
	virtual void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage);

	Ogre::Root* getRoot(void) const                         { return mRoot; }
	Ogre::RenderWindow* getRenderWindow(void) const         { return mRenderWindow; }
	void setRenderWindow(Ogre::RenderWindow* renderWin);
	Ogre::SceneManager* getSceneManager(void) const         { return mSceneManager; }
	Ogre::Camera* getCamera(void) const                     { return mCamera; }
	Ogre::CompositorWorkspace* getCompositorWorkspace(void) const { return mWorkspace; }

protected:
	static void addResourceLocation(const Ogre::String &archName, const Ogre::String &typeName,
		const Ogre::String &secName);
	virtual void setupResources(void);
	virtual void registerHlms(void);
	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	/// Virtual so that advanced samples such as Sample_Compositor can override this
	/// method to change the default behavior if setupCompositor() is overridden, be
	/// aware @mBackgroundColour will be ignored
	virtual Ogre::CompositorWorkspace* setupCompositor(void);

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void) {}
	void createScene01(void);

private:
	void initialiseLogging(void);
	void initialiseOgre(Ogre::NameValuePairList params, int width, int height);

	//Logging
	Ogre::Log* mInternalOgreLog;
	Ogre::LogManager* mInternalOgreLogManager;

	//Ogre Stuff
	Ogre::RenderSystem* mActiveRenderSystem;
	Ogre::RenderSystem* mOpenGL3PlusRenderSystem;
	Ogre::RenderSystem* mDirect3D11RenderSystem;

	//Misc
	unsigned int mFrameCounter;

	Ogre::ColourValue   mBackgroundColour;

	Ogre::Root                  *mRoot;
	Ogre::RenderWindow          *mRenderWindow;
	Ogre::SceneManager          *mSceneManager;
	Ogre::Camera                *mCamera;
	Ogre::CompositorWorkspace   *mWorkspace;
	Ogre::String                mResourcePath;
	bool mIsInitialised;

	Ogre::SceneNode     *mSceneNode;
};

END_NAMESPACE_GAMEEDITOR

#endif
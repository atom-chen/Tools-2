#ifndef QTOGRE_APPLICATION_H_
#define QTOGRE_APPLICATION_H_

#include <Ogre.h>
#include <OgreLog.h>
#include <string>

class GameLogic;

class OgreSys : public Ogre::LogListener
{
public:
	OgreApp();
	~OgreApp();

	unsigned int frameCount(void) const;
	void setAutoUpdateInterval(int intervalInMilliseconds);
	void setAutoUpdateEnabled(bool autoUpdateEnabled);

	bool isOpenGLAvailable(void) const;
	bool isDirect3D9Available(void) const;

public:
	void initialise(void);
	void shutdown(void);
	void update(void);
	void loadResourcePathsFromConfigFile(std::string filename);

private:
	void initialiseLogging(void);
	void initialiseOgre(void);

	//Logging
	Ogre::Log* mInternalOgreLog;
	Ogre::LogManager* mInternalOgreLogManager;

	//Ogre Stuff
	Ogre::RenderSystem* mActiveRenderSystem;
	Ogre::RenderSystem* mOpenGLRenderSystem;
	Ogre::RenderSystem* mDirect3D9RenderSystem;
	Ogre::Root* mRoot;
	//Misc
	unsigned int mFrameCounter;
	GameLogic* mGameLogic;
};

#endif
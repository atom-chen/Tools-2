#ifndef __SINGLETON_H
#define __SINGLETON_H

#include <assert.h>
#include "GlobalDefine.h"

BEGIN_NAMESPACE_GAMEEDITOR

template<class T>
class AIEDITOR_EXPORT Singleton
{
protected:
	static T* ms_Singleton;

public:
	Singleton()
	{
		assert(!ms_Singleton);
		ms_Singleton = static_cast< T* >(this);
	}

	~Singleton()
	{
		assert(ms_Singleton);
		ms_Singleton = 0;
	}

	static T& getSingleton()
	{
		assert(ms_Singleton);
		return (*ms_Singleton);
	}

	static T* getSingletonPtr()
	{
		return ms_Singleton;
	}
};

END_NAMESPACE_GAMEEDITOR

#endif				// SINGLETON_H
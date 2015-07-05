#ifndef __SINGLETON_H
#define __SINGLETON_H

#include <assert.h>
#include "GlobalDefine.h"

BEGIN_NAMESPACE_AIEDITOR

template<class T>
class AIEDITOR_EXPORT Singleton
{
protected:
	static T* ms_Singleton;

public:
	Singleton()
	{
		assert(!ms_Singleton);
#if defined( _MSC_VER ) && _MSC_VER < 1200
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		ms_Singleton = (T*)((int)this + offset);
#else
		ms_Singleton = static_cast< T* >(this);
#endif
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

END_NAMESPACE_AIEDITOR

#endif				// SINGLETON_H
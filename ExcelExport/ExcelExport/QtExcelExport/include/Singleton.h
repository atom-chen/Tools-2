#ifndef _SINGLETON_H
#define _SINGLETON_H

// #include "MemLeakCheck.h"	// 内存泄露检测头文件不用包含，只要包含源文件就行了

#include "Platform.h"

BEGIN_NAMESPACE

template<class T>
class Singleton
{
private:
	static T* msSingleton;

public:
	static T* getSingletonPtr()
	{
		if(msSingleton == NULL)
		{
			msSingleton = new T();
		}
		return msSingleton;
	}
};

END_NAMESPACE

//#include "UnMemLeakCheck.h"

#endif				// SINGLETON_H
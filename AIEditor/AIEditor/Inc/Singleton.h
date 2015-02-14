﻿#ifndef __SINGLETON_H
#define __SINGLETON_H

#include "GlobalDefine.h"

BEGIN_NAMESPACE_AIEDITOR

template<class T>
class AIEDITOR_EXPORT Singleton
{
protected:
	static T* m_sSingleton;

public:
	static T* getSingletonPtr()
	{
		if (m_sSingleton == NULL)
		{
			m_sSingleton = new T();
		}
		return m_sSingleton;
	}
};

END_NAMESPACE_AIEDITOR

#endif				// SINGLETON_H
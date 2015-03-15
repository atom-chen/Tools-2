#ifndef __UtilWrap_H
#define __UtilWrap_H

#include "tinyxml2.h"
namespace EasyOgreExporter
{
	class UtilWrap
	{
	public:
		static bool isTinyXmlSuccess(tinyxml2::XMLError result);
	};
}

#endif
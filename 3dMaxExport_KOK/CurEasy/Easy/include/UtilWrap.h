#ifndef __UtilWrap_H
#define __UtilWrap_H

#include "ExPrerequisites.h"
#include "tinyxml2.h"

namespace EasyOgreExporter
{
	class UtilWrap
	{
	public:
		static bool isTinyXmlSuccess(tinyxml2::XMLError result);
		static IGameModifier* getGameModifierByGameNode(IGameNode* pGameNode, char* modifierName);
		static bool isStrEqual(char* aChar, char* bChar);
		static char* W2A(const TCHAR* s);
		static TCHAR* A2W(const char* s);
	};
}

#endif
#include "UtilWrap.h"
#include <string.h>

namespace EasyOgreExporter
{
	bool UtilWrap::isTinyXmlSuccess(tinyxml2::XMLError result)
	{
		return tinyxml2::XML_SUCCESS == result || tinyxml2::XML_NO_ERROR == result;
	}

	bool UtilWrap::isStrEqual(char* aChar, char* bChar)
	{
		return strcmp(aChar, bChar) == 0;
	}

	char* UtilWrap::W2A(const TCHAR* s) 
	{
#ifdef UNICODE
		int size = (wcslen(s) + 1) * 2;
		char *out = (char*)malloc(size);
		wcstombs(out, s, size);
		return out;
#else
		return strdup(s);
#endif
	}

	TCHAR* UtilWrap::A2W(const char* s) 
	{
#ifdef UNICODE
		int size = (strlen(s) + 1) * sizeof(TCHAR);
		TCHAR *out = (TCHAR*)malloc(size);
		mbstowcs(out, s, size);
		return out;
#else
		return strdup(s);
#endif
	}

	IGameModifier* UtilWrap::getGameModifierByGameNode(IGameNode* pGameNode, char* modifierName)
	{
		IGameObject* pGameObject = pGameNode->GetIGameObject();
		if (pGameObject)
		{
			int numModifiers = pGameObject->GetNumModifiers();
			{
				for (int i = 0; i < numModifiers; ++i)
				{
					IGameModifier* pGameModifier = pGameObject->GetIGameModifier(i);
					{
						if (pGameModifier)
						{
							MSTR className = pGameModifier->GetClassName();
							char * className_ptr = W2A(className);
							if (isStrEqual(className_ptr, modifierName))
							{
								return pGameModifier;
							}
						}
					}
				}
			}
		}

		return nullptr;
	}
}
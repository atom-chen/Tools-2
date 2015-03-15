#include "UtilWrap.h"

namespace EasyOgreExporter
{
	bool UtilWrap::isTinyXmlSuccess(tinyxml2::XMLError result)
	{
		return tinyxml2::XML_SUCCESS == result || tinyxml2::XML_NO_ERROR == result;
	}
}
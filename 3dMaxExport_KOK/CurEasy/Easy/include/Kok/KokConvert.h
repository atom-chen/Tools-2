#ifndef _KOKCONVERT_H
#define _KOKCONVERT_H

#include "ExOgreConverter.h"

namespace EasyOgreExporter
{
	class KokConvert : ExOgreConverter
	{
	public:
		KokConvert(IGameScene* pIGameScene, ParamList params);
		~KokConvert();

		void exportKok();
	};
}

#endif
#ifndef _stNullUserCmd_h
#define _stNullUserCmd_h

#include "zType.h"

#pragma pack(1)

namespace Cmd
{
	//////////////////////////////////////////////////////////////
	// 空指令定义开始
	//////////////////////////////////////////////////////////////
	enum eNullUserCmd
	{
		NULL_USERCMD_PARA = 0,
	};

	class stNullUserCmd
	{
		public BYTE byCmd;
		public BYTE byParam;
		public DWORD dwTimestamp;

		public stNullUserCmd()
		{
			byCmd = 0;
			byParam = 0;
			dwTimestamp = 0;
		}
	};

}

#pragma pack()

#endif
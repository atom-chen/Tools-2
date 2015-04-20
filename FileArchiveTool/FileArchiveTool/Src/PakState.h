#ifndef __PakState_H
#define __PakState_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

enum EPakState
{
	ePS_NONE,		// 默认状态
	ePS_PAKING,		// 正在打包
	ePS_PAKEND,		// 打包结束
};

class FILEARCHIVETOOL_EXPORT PakState
{
protected:
	EPakState m_curState;

public:
	PakState();
	~PakState();

	void toggleState(EPakState state);
	bool isEqualState(EPakState state);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
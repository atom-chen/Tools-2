#ifndef __PakState_H
#define __PakState_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

enum EPakState
{
	ePS_NONE,		// Ĭ��״̬
	ePS_PAKING,		// ���ڴ��
	ePS_PAKEND,		// �������
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
#include "PakState.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakState::PakState()
{
	m_curState = ePS_NONE;
}

PakState::~PakState()
{

}

void PakState::toggleState(EPakState state)
{
	m_curState = state;
}

bool PakState::isEqualState(EPakState state)
{
	return m_curState == state;
}

END_NAMESPACE_FILEARCHIVETOOL
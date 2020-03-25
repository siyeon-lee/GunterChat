#include "syFiniteState.h"



syFiniteState::syFiniteState()
{
}


syFiniteState::~syFiniteState()
{
}
INT syFiniteState::GetPtr(DWORD dwKey)
{
	TItor itor = m_List.find(dwKey);
	if (itor == m_List.end()) return -1;
	return (INT)itor->second;
}

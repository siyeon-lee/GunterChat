#include "syFSM.h"
#include "syStd.h"


syFSM::syFSM()
{
}


syFSM::~syFSM()
{
}

syFiniteState* syFSM::GetPtr(DWORD dwKey)
{
	TItor itor = m_List.find(dwKey);
	if (itor == m_List.end()) return nullptr;
	syFiniteState* data = itor->second.get();
	return data;
}
void syFSM::Add(DWORD dwInputState, DWORD dwEvent, DWORD dwOutputState)
{
	TItor iter;
	iter = m_List.find(dwInputState);

	syFiniteState* pFindState = nullptr;
	if (iter == m_List.end())
	{
		auto data = make_shared<syFiniteState>();
		m_List[dwInputState] = data;
		pFindState = data.get();
	}
	else
	{
		pFindState = iter->second.get();
	}
	pFindState->m_List[dwEvent] = dwOutputState;
}
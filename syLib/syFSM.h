#pragma once
#include "syFiniteState.h"

class syFSM : public sySingleton<syFSM>
{
	friend class sySingleton<syFSM>;
public:
	syFSM();
	~syFSM();

public:
	typedef std::map<DWORD, shared_ptr<syFiniteState> >::iterator TItor;
	std::map<DWORD, shared_ptr<syFiniteState>>  m_List;
public:
	void Add(DWORD dwInputState, DWORD dwEvent, DWORD dwOutputState);
	syFiniteState* GetPtr(DWORD dwKey);
};

#define I_Fsm syFSM::GetInstance()
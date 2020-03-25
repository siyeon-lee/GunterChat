#pragma once
#include "syStd.h"

enum syEvent 
{
	EVENT_TILECOLL, EVENT_PLAYERCOLL, EVENT_FINDTARGET, EVENT_LOSTTARGET, EVENT_DEAD, EVENT_COUNTER
};
enum syAction
{
	ACTION_ATTACK,
	ACTION_DEAD,
	ACTION_MOVE,
	ACTION_STAND,
	ACTION_COUNT
};

class syFsm;
class syFiniteState
{
	friend class syFsm;
public:
	syFiniteState();
	virtual ~syFiniteState();

public:
	typedef std::map<DWORD, DWORD>::iterator TItor;
	std::map<DWORD, DWORD>  m_List;
public:
	INT GetPtr(DWORD dwKey);
};


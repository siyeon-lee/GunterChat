#pragma once
#include "syStd.h"
#include "syBackground.h"
#include "syCharacter.h"
#include "syEnemyState.h"
#include "syFSM.h"
#include "syCollision.h"
enum syBITMAPMARIO
{
	MARIO_FORWORD,
	MARIO_BACKWORD,
	MARIO_IDLEFORWORD,
	MARIO_IDLEBACKWORD,
	MARIO_DEAD,
	MARIO_COUNT
};

class syEnemy : public syCharacter
{
public:
	syEnemy();
	virtual ~syEnemy();
public:
	syEnemyState*	m_pAction;
	syEnemyState*	m_pActionList[4];
	DWORD			m_dwCurrentState;
public:
	bool Init();
	bool Frame();
	void ProcessAI(syCharacter* pTarget);
public:
	void SetTransition(DWORD dwEvent);
};


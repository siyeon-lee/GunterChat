#include "syEnemy.h"
#include "syInput.h"
#include "syEnemyATTACK.h"
#include "syEnemyDEAD.h"
#include "syEnemyMove.h"
#include "syEnemySTAND.h"
//
//enum syAction
//{
//	ACTION_ATTACK,
//	ACTION_DEAD,
//	ACTION_MOVE,
//	ACTION_STAND,
//	ACTION_COUNT
//};


syEnemy::syEnemy()
{
}

syEnemy::~syEnemy()
{
	
}
bool syEnemy::Init()
{
	m_pActionList[0] = new syEnemyATTACK(this);
	m_pActionList[1] = new syEnemyDEAD(this);
	m_pActionList[2] = new syEnemyMove(this);
	m_pActionList[3] = new syEnemySTAND(this);
	m_pAction = m_pActionList[2];
	m_dwCurrentState = ACTION_MOVE;
	return true;
}
bool syEnemy::Frame()
{
	syCharacter::Frame();
	return true;
}
void syEnemy::ProcessAI(syCharacter* pTarget)
{
	m_pAction->Process(pTarget);
}
void syEnemy::SetTransition(DWORD dwEvent)
{
	// input -> event -> output

	syFiniteState* pState = I_Fsm.GetPtr((m_dwCurrentState));
	if (pState == nullptr) return;

	DWORD dwAction = pState->GetPtr(dwEvent);
	m_pAction = m_pActionList[dwAction];
	m_dwCurrentState = dwAction;
}
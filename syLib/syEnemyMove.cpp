#include "syEnemyMove.h"
#include "syEnemy.h"


syEnemyMove::syEnemyMove(syEnemy* pParent) : syEnemyState(pParent)
{
}


syEnemyMove::~syEnemyMove()
{
}

void syEnemyMove::Process(syCharacter* pTarget)
{
	if(m_pOwner->m_bDead) return;

	static float fTime = 0;
	fTime += g_fSecondPerFrame;
	static float ran = rand() % 5;

	if (syCollision::RectInRect(m_pOwner->m_rtColl, pTarget->m_rtColl))
	{
		m_pOwner->SetTransition(EVENT_DEAD);
		return;
	}


	if (m_pOwner->isFront)
	{
		m_pOwner->SetSpriteBitmap(MARIO_FORWORD);
		m_pOwner->player_pos.x += 50 * g_fSecondPerFrame;
	}
	else
	{
		m_pOwner->SetSpriteBitmap(MARIO_BACKWORD);
		m_pOwner->player_pos.x -= 50 * g_fSecondPerFrame;
	}

	if (m_pOwner->m_rtColl.left < 1)
	{
		m_pOwner->isFront = true;
	}
	if (m_pOwner->m_rtColl.right > 639)
	{
		m_pOwner->isFront = false;
	}

	if (fTime > ran && m_pOwner->isStand)
	{
		fTime = 0.0f;
		ran = rand() % 5;
		m_pOwner->SetYSPEED(200);
		m_pOwner->isFront = rand() % 2;
	}


}
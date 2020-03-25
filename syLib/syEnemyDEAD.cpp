#include "syEnemyDEAD.h"
#include "syEnemy.h"


syEnemyDEAD::syEnemyDEAD(syEnemy* pParent) : syEnemyState(pParent)
{
}


syEnemyDEAD::~syEnemyDEAD()
{
}
void syEnemyDEAD::Process(syCharacter* pTarget)
{
	static float fTime = 0;
	fTime += g_fSecondPerFrame;

	if (fTime > 1.0f)
	{
		if (m_pOwner->spritenum == MARIO_DEAD)
		{
			m_pOwner->m_bDead = true;
		}

		if (fTime > 5.0f)		//마리오 리젠
		{
			m_pOwner->m_bDead = false;
			m_pOwner->isFront = true;
			m_pOwner->SetSpriteBitmap(MARIO_FORWORD);
			m_pOwner->syCharacter::Frame();
			m_pOwner->player_pos = syPoint(300,0);
			fTime = 0.0f;
			m_pOwner->SetTransition(EVENT_FINDTARGET);
			return;
		}
	}
	if (m_pOwner->m_bDead) return;

	if (m_pOwner->spritenum == MARIO_DEAD)
	{
		m_pOwner->syCharacter::Frame();
		return;
	}
	//공격 여부 판정
	float delsize =pTarget->player_pos.y - m_pOwner->player_pos.y;
	if (pTarget->player_pos.y + 5 < m_pOwner->player_pos.y && pTarget->m_bDead!= true)
	{
		m_pOwner->SetSpriteBitmap(MARIO_DEAD);
		m_pOwner->SetYSPEED(100);
		m_pOwner->syCharacter::Frame(); 
		pTarget->ySpeed = 300;
		pTarget->syCharacter::Frame();
		g_score += 100;
		return;
	}

	pTarget->m_bDead = true;
}
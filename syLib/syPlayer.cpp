#include "syPlayer.h"
syPlayer::syPlayer()
{
}


syPlayer::~syPlayer()
{
}

bool  syPlayer::Frame()
{
	//��������Ʈ
	if (isFront)
	{
		//jumping
		if (isStand == false || g_ActionInput.bUPKEY == KEY_HOLD)
		{
			SetSpriteBitmap(GUNTER_JUMPINGFORWORD);
		}			
		else
		{	//walking
			if (g_ActionInput.bRIGHTKEY == KEY_HOLD)
			{
				SetSpriteBitmap(GUNTER_FORWORD);	
			}
			//idle
			else
			{
				SetSpriteBitmap(GUNTER_IDLEFORWORD);
			}
		}
	}
	//�� ���� ���
	else if(!isFront)
	{
		//jumping
		if (isStand == false || g_ActionInput.bUPKEY == KEY_HOLD)
		{
			SetSpriteBitmap(GUNTER_JUMPINGBACKWORD);
		}
		else
		{
			//walking
			if (g_ActionInput.bLEFTKEY == KEY_HOLD)
			{
				SetSpriteBitmap(GUNTER_BACKWORD);
			}
			//idle
			else
			{
				SetSpriteBitmap(GUNTER_IDLEBACKWORD);
			}
		}
	}


	//������
	if (g_ActionInput.bUPKEY == KEY_PUSH)
	{
		if (isStand)
		{
			ySpeed = YSPEED;
		}
	}
	if (g_ActionInput.bLEFTKEY == KEY_HOLD)
	{
		isFront = false;
		player_pos.x -= m_fSpeed * g_fSecondPerFrame;
	}
	if (g_ActionInput.bRIGHTKEY == KEY_HOLD)
	{
		isFront = true;
		player_pos.x += m_fSpeed * g_fSecondPerFrame;
	}
	syCharacter::Frame();
	return true;
}

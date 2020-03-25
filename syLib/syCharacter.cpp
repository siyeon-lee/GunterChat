#include "syCharacter.h"
int g_score;


syCharacter::syCharacter()
{
}


syCharacter::~syCharacter()
{
}

bool syCharacter::Frame()
{
	//player_pos = m_info.InitPos;
	player_pos.y -= ySpeed * g_fSecondPerFrame;
	m_info.InitPos = player_pos;
	sySprite::Frame();
	ySpeed -= 5;
	RECT rt;
	rt.top = m_rtObj.top * m_rtFactor;
	rt.bottom = m_rtObj.bottom * m_rtFactor;
	rt.right = m_rtObj.right * m_rtFactor;
	rt.left = m_rtObj.left * m_rtFactor;
	SetDrawRect(player_pos, rt);
	return true;
}
bool syCharacter::Render()
{

	if (m_bDead == true) return true;
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_fAlpha;
	if (m_pBitmap->m_BitmapInfo.bmBitsPixel == 32)
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		m_pBitmap->Draw(m_rtDraw, m_info.rtList[m_iCurrentFrame], bf);
	}
	else
	{
		m_pBitmap->Draw(m_rtDraw,
			m_info.rtList[m_iCurrentFrame], SRCCOPY);
	}
	//SetROP2(g_hOffScreenDC, R2_NOTXORPEN);
	//int PrevMode = Rectangle(g_hOffScreenDC,
	//	m_rtColl.left,
	//	m_rtColl.top,
	//	m_rtColl.right,
	//	m_rtColl.bottom);
	//SetROP2(g_hOffScreenDC, PrevMode);
	return true;

}
bool  syCharacter::Release()
{
	sySprite::Release();

	return true;
}
bool syCharacter::setStand(sySprite* tile)
{
	isStand = false;
	float rheight = (tile->m_rtColl.top - tile->m_rtColl.bottom) / 2;
	if (syCollision::RectInRect(m_rtColl, tile->m_rtColl))
	{
		//위에서 추락
		if (m_rtColl.bottom >= tile->m_rtColl.top + rheight && ySpeed <= 0)
		{
			player_pos.y = tile->m_rtColl.top - (m_rtDraw.bottom / 2);
			ySpeed = 0.0f;
			isStand = true;
			return true;
		}
		//밑에서 올라오는 상황
		else if (m_rtColl.top <= tile->m_rtColl.bottom - rheight && ySpeed >= 0)
		{
			player_pos.y = tile->m_rtColl.bottom + (m_rtDraw.bottom / 2);
			ySpeed = -YSPEED;

		}
		//return true;
	}
	return false;
};

void  syCharacter::insertChar(sySpriteData* pGunter)
{
	pSpriteData = pGunter;
}
void  syCharacter::SetSpriteBitmap(int spriteNum)
{

	if (spritenum == spriteNum) return;
	m_iCurrentFrame = 0;
	Set(pSpriteData->m_SpriteListData[spriteNum], pSpriteData->m_iBitmapID, pSpriteData->m_iMaskBitmapID);
	spritenum = spriteNum;

}
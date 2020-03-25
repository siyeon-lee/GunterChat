#include "sySprite.h"



sySprite::sySprite()
{
	m_fTmpTime = 0.0f;
	m_fDeltaTime = 0.0f;
	m_iCurrentFrame = 0;
	m_iSpriteID = 0;
	m_bDead = false;
	m_bSceneChange = false;
}


sySprite::~sySprite()
{
}


bool  sySprite::Set(syObjectInfo info, int bitmapid, int mask)
{
	m_info = info;
	m_rtObj = m_info.rtClient;

	if (info.fLifeTime == 0.0f)
	{
		m_info.bLoop = true;
	}
	if (m_info.iBitmapID == -1)
	{
		m_pBitmap = I_BitmapMgr.GetPtr(bitmapid);
	}
	else
	{
		m_pBitmap = I_BitmapMgr.GetPtr(m_info.iBitmapID);
	}
	if (m_info.iMaskID == -1)
	{
		m_pBitmapMask = I_BitmapMgr.GetPtr(mask);
	}
	else
	{
		m_pBitmapMask = I_BitmapMgr.GetPtr(m_info.iMaskID);
	}
	m_fDeltaTime = m_info.fTime / m_info.iNumFrame;

	syObject::SetPos(m_info.InitPos);
	return true;
}

bool  sySprite::Init()
{
	return true;
}

bool  sySprite::Frame()
{
	if (m_info.bLoop == false)
	{
		m_info.fLifeTime -= g_fSecondPerFrame;
		if (m_info.fLifeTime <= 0) m_bDead = true;
	}
	if (m_bDead == true) return true;
	if (m_info.iNumFrame <= 1)
	{
		syObject::Set(m_info.InitPos, m_info.rtList[m_iCurrentFrame], m_info.fSpeed);
		return true;
	}

	m_fTmpTime += g_fSecondPerFrame;
	if (m_fTmpTime > m_fDeltaTime)
	{
		m_iCurrentFrame++;
		if (m_iCurrentFrame >= m_info.iNumFrame)
		{
			m_iCurrentFrame = 0;
		}
		m_fTmpTime = 0.0f;
	}
	syObject::Set(m_info.InitPos, m_info.rtList[m_iCurrentFrame], m_info.fSpeed);
	return true;
}

bool  sySprite::Render()
{
	if (m_bDead == true) return true;

	RECT rt = m_info.rtList[m_iCurrentFrame];
	rt.left = m_Pos.x - (rt.right / 2);
	rt.top = m_Pos.y - (rt.bottom / 2);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_fAlpha;

	Draw(SRCCOPY);

	return true;
};
bool  sySprite::Release()
{
	m_info.rtList.clear();
	return true;
}

void  sySprite::Draw(DWORD dwMode)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_fAlpha;
	if (m_pBitmap->m_BitmapInfo.bmBitsPixel == 32)
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		m_pBitmap->Draw(m_rtDraw.left, m_rtDraw.top,
			m_info.rtList[m_iCurrentFrame], bf);
	}
	else
	{
		bf.AlphaFormat = AC_SRC_OVER;
		m_pBitmap->Draw(m_rtDraw.left, m_rtDraw.top,
			m_info.rtList[m_iCurrentFrame], dwMode);
	}
}
void  sySprite::DrawCenter(DWORD dwMode)
{
	RECT rt = m_info.rtList[m_iCurrentFrame];
	rt.left = m_Pos.x - (rt.right / 2);
	rt.top = m_Pos.y - (rt.bottom / 2);
	m_pBitmap->Draw(rt.left, rt.top,
		m_info.rtList[m_iCurrentFrame], dwMode);
}
void  sySprite::Draw(int x, int y, DWORD dwMode)
{
	m_pBitmap->Draw(x, y,
		m_info.rtList[m_iCurrentFrame], dwMode);
}
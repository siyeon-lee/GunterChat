#include "syButtonCtrl.h"
#include "syCollision.h"
#include "syBitmapMgr.h"

syUIComponent* syButtonCtrl::Clone()
{
	return new syButtonCtrl(*this);
}

bool  syButtonCtrl::Frame()
{
	
	//sprite frame
	if (!sySprite::Frame())
	{
		return false;
	}

	//button state
	if (m_bSelect && g_ActionInput.bLeftClick == KEY_UP)
	{
		if (syCollision::RectInPt(m_rtColl, g_MousePos))
		{
			//DWORD dwWParam = MAKELONG(m_iIndexType, WM_GAMESTART);
			DWORD dwWParam = MAKELONG(m_iIndexType, WM_GAMESTART);
			DWORD dwLParam = MAKELONG(0, KEY_UP);
			PostMessage(g_hWnd, WM_UICONTRLMSG, dwWParam, dwLParam);
		}
	}
	if (m_bCollision == true)
	{
		m_pCurrentBitmap = m_pStateBitmap[0];
		m_bSelect = false;
		if (syCollision::RectInPt(m_rtColl, g_MousePos))
		{
			if (g_ActionInput.bLeftClick == KEY_HOLD)
			{
				m_pCurrentBitmap = m_pStateBitmap[2];
				m_bSelect = true;
			}
			else
			{
				m_pCurrentBitmap = m_pStateBitmap[1];
			}
		}
	}
	int iNumButton = 0;
	for (auto button : m_ctrlList)
	{
		syButtonCtrl* pButton = (syButtonCtrl*)button;
		iNumButton += button->m_info.rtClient .bottom;
		if (iNumButton >= m_info.rtClient.bottom)
		{
			break;
		}
		pButton->Frame();
	}
	return true;
}

bool  syButtonCtrl::Release()
{
	sySprite::Release();
	return true;
}


void syButtonCtrl::SetStateButton
(int nor, int sel, int pus, int dis, bool bcoll)
{
	m_iNormal = nor;
	m_iHover = sel;
	m_iPush = pus;
	m_iDisable = dis;
	m_bSelect = false;
	m_pStateBitmap[0] = I_BitmapMgr.GetPtr(m_iNormal);
	m_pStateBitmap[1] = I_BitmapMgr.GetPtr(m_iHover);
	m_pStateBitmap[2] = I_BitmapMgr.GetPtr(m_iPush);
	m_pStateBitmap[3] = I_BitmapMgr.GetPtr(m_iDisable);
	m_bCollision = bcoll;
	m_pCurrentBitmap = m_pStateBitmap[0];
}


bool  syButtonCtrl::Set(syObjectInfo info, int id, int mask)
{
	if (!sySprite::Set(info, id, mask))
	{
		return false;
	}
	m_pCurrentBitmap = m_pBitmap;
	return true;
}

void syButtonCtrl::Draw(DWORD dwMode)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_fAlpha;
	if (m_pBitmap->m_BitmapInfo.bmBitsPixel == 32)
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		m_pCurrentBitmap->Draw(m_rtDraw.left, m_rtDraw.top,	m_info.rtList[m_iCurrentFrame], bf);
	}
	else
	{
		bf.AlphaFormat = AC_SRC_OVER;
		m_pCurrentBitmap->Draw(m_rtDraw.left, m_rtDraw.top,	m_info.rtList[m_iCurrentFrame], dwMode);	//dwMode = SRCCOPY
	}

	int iNumButton = 0;
	for (auto button : m_ctrlList)
	{
		iNumButton += button->m_info.rtClient.bottom;
		if (iNumButton >= m_info.rtClient.bottom)
		{
			break;
		}
		syButtonCtrl* pButton = (syButtonCtrl*)button;
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = m_fAlpha;
		if (pButton->m_pCurrentBitmap->m_BitmapInfo.bmBitsPixel == 32)
		{
			bf.AlphaFormat = AC_SRC_ALPHA;
			pButton->m_pCurrentBitmap->Draw(pButton->m_rtDraw, pButton->m_info.rtList[pButton->m_iCurrentFrame], bf);
		}
		else
		{
			bf.AlphaFormat = AC_SRC_OVER;
			pButton->m_pCurrentBitmap->Draw(
				pButton->m_rtDraw,
				pButton->m_info.rtList[pButton->m_iCurrentFrame], SRCCOPY);
		}
	}
}


syButtonCtrl::syButtonCtrl()
{
	m_pCurrentBitmap = nullptr;
	m_bCollision = false;
}


syButtonCtrl::~syButtonCtrl()
{
}

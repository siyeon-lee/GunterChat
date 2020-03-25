#include "syListCtrl.h"



syListCtrl::syListCtrl()
{
	m_iStart = 0;
	m_iEnd = 0;
	m_iSubButtonHeight = 25; // 서브 버튼의 세로 크기
	m_iOffsetBaseX = 10; // 부모의 시작위치로 부터 떨어진 거리
	m_iOffsetBaseY = 10;
	m_iButtonStep = 0;
}


syListCtrl::~syListCtrl()
{
}


syUIComponent* syListCtrl::Clone()
{
	return new syListCtrl(*this);
}
void syListCtrl::SetAttribute(
	int iSubButtonHeight, int iOffsetBaseX, int iOffsetBaseY, int  iButtonStep)
{
	m_iSubButtonHeight = iSubButtonHeight;
	m_iOffsetBaseX = iOffsetBaseX;
	m_iOffsetBaseY = iOffsetBaseY;
	m_iButtonStep = iButtonStep;
}

void syListCtrl::Draw(DWORD dwMode)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_fAlpha;
	if (m_pCurrentBitmap->m_BitmapInfo.bmBitsPixel == 32)
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		m_pCurrentBitmap->Draw(m_rtDraw, m_info.rtList[m_iCurrentFrame], bf);
	}
	else
	{
		bf.AlphaFormat = AC_SRC_OVER;
		m_pCurrentBitmap->Draw(
			m_rtDraw,
			m_info.rtList[m_iCurrentFrame], SRCCOPY);
	}

	//for (auto button : m_ctlList)
	for (int iCnt = m_iStart; iCnt < m_iEnd; iCnt++)
	{
		syButtonCtrl* pButton = (syButtonCtrl*)m_ctrlList[iCnt];
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = m_fAlpha;
		if (pButton->m_pCurrentBitmap->m_BitmapInfo.bmBitsPixel == 32)
		{
			bf.AlphaFormat = AC_SRC_ALPHA;
			pButton->m_pCurrentBitmap->Draw(pButton->GetDrawRect(), pButton->m_info.rtList[pButton->m_iCurrentFrame], bf);
		}
		else
		{
			bf.AlphaFormat = AC_SRC_OVER;
			pButton->m_pCurrentBitmap->Draw(
				pButton->GetDrawRect(),
				pButton->m_info.rtList[pButton->m_iCurrentFrame], SRCCOPY);
		}
	}
}

bool syListCtrl::Frame()
{
	// sprite frame
	if (!sySprite::Frame())
	{
		return false;
	}
	//button state
	if (m_bSelect && g_ActionInput.bLeftClick == KEY_UP)
	{
		if (syCollision::RectInPt(m_rtColl, g_MousePos))
		{
			m_bCollision = true;
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
		iNumButton += button->m_info.rtClient.bottom;
		if (iNumButton >= m_info.rtClient.bottom)
		{
			break;
		}
		pButton->Frame();
		//button state
		if (syCollision::RectInPt(pButton->m_rtColl, g_MousePos))
		{
			if (g_ActionInput.bLeftClick == KEY_PUSH)
			{
				DWORD dwWParam = MAKELONG(m_iIndexType, WM_BUTTONCLICK);
				DWORD dwLParam = MAKELONG(pButton->m_iIndexType, KEY_PUSH);
				PostMessage(g_hWnd, WM_UICONTRLMSG, dwWParam, dwLParam);
			}
		}

	}
	return true;
}
bool syListCtrl::Release()
{
	for (auto data : m_btnList)
	{
		m_btnList.pop_back();
	}
	syButtonCtrl::Release();
	return true;
}
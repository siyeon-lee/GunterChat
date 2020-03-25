#include "syUIComponent.h"
#include "syImgCtrl.h"


syUIComponent::syUIComponent()
{
	m_pOwner = nullptr;
}


syUIComponent::~syUIComponent()
{
}

LRESULT	syUIComponent::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UINT msgControll = HIWORD(wParam);
	switch (msgControll)
	{
	case WM_BUTTONCLICK:
	{
		UINT b = LOWORD(wParam);
		short c = HIWORD(lParam);
		short d = LOWORD(lParam);
		MessageBox(g_hWnd, L"WM_BUTTONCLICK", std::to_wstring(d).c_str(), MB_OK);
	}break;
	}
	return 1;
}

void syUIComponent::Add(syUIComponent* pComponent)
{
	m_ctrlList.push_back(pComponent);
}

void syUIComponent::SetRect(int iRect, syVertex Start, syVertex Middle, syVertex End, int iBitmapID, int iMaskBitmapID)
{
	RECT rtClient = { Start.p.x,	Start.p.y,
					Middle.p.x - Start.p.x,
					End.p.y - Start.p.y };
	RECT rt = { Start.t.x,	Start.t.y,
						Middle.t.x - Start.t.x,
						End.t.y - Start.t.y };

	syObjectInfo info;
	info.InitPos.x = (Middle.p.x + Start.p.x) / 2;
	info.InitPos.y = (End.p.y + Start.p.y) / 2;
	info.rtClient = rtClient;
	info.rtList.push_back(rt);

	syImgCtrl* pCtl = new syImgCtrl();
	pCtl->Set(info, iBitmapID, iMaskBitmapID);
	m_ctrlList.push_back(pCtl);
}
void	syUIComponent::Gen(syRect rt, syRect rtSrc, int iBitmapID, int iMaskBitmapID)
{
	//rtDraw
	float fClientX0 = 0.1f;
	float fClientX1 = 0.1f;
	float fClientY0 = 0.1f;
	float fClientY1 = 0.1f;
	// rtSrc
	float fOffestX0 = 0.2f;
	float fOffestX1 = 0.2f;
	float fOffestY0 = 0.33f;
	float fOffestY1 = 0.33f;
	m_Vertex[0] =
	{ rt.left,rt.top, rtSrc.left, rtSrc.top };
	m_Vertex[1] =
	{ rt.left + (rt.right*fClientX0),rt.top,
		rtSrc.left + (rtSrc.right*fOffestX0),rtSrc.top };
	m_Vertex[2] =
	{ rt.left + (rt.right*(1.0f - fClientX1)),rt.top,
		rtSrc.left + (rtSrc.right*(1.0f - fOffestX1)),rtSrc.top
	};
	m_Vertex[3] = { rt.left + rt.right,rt.top,
	rtSrc.left + rtSrc.right,rtSrc.top };

	m_Vertex[4] = { rt.left,rt.top + (rt.bottom*fClientY0),
	rtSrc.left,rtSrc.top + (rtSrc.bottom*fOffestY0) };
	m_Vertex[5] = { rt.left + (rt.right*fClientX0),
								rt.top + (rt.bottom*fClientY0),
		rtSrc.left + (rtSrc.right*fOffestX0),
		rtSrc.top + (rtSrc.bottom*fOffestY0)
	};
	m_Vertex[6] = { rt.left + (rt.right*(1.0f - fClientX1)),
								rt.top + (rt.bottom*fClientY0),
		rtSrc.left + (rtSrc.right*(1.0f - fOffestX1)),
		rtSrc.top + (rtSrc.bottom*fOffestY0) };
	m_Vertex[7] = { rt.left + rt.right,
								rt.top + (rt.bottom*fClientY0),
								rtSrc.left + rtSrc.right,
								rtSrc.top + (rtSrc.bottom*fOffestY0) };

	m_Vertex[8] = {
		rt.left,rt.top + (rt.bottom*(1.0f - fClientY1)),
		rtSrc.left,rtSrc.top + (rtSrc.bottom*(1.0f - fOffestY1)) };
	m_Vertex[9] = { rt.left + (rt.right*fClientX0),
								rt.top + (rt.bottom*(1.0f - fClientY1)) ,
								rtSrc.left + (rtSrc.right*fOffestX0),
								rtSrc.top + (rtSrc.bottom*(1.0f - fOffestY1)) };
	m_Vertex[10] = { rt.left + (rt.right*(1.0f - fClientX1)),
								rt.top + (rt.bottom*(1.0f - fClientY1)),
	rtSrc.left + (rtSrc.right*(1.0f - fOffestX1)),
	rtSrc.top + (rtSrc.bottom*(1.0f - fOffestY1))
	};
	m_Vertex[11] = { rt.left + rt.right,
								rt.top + (rt.bottom*(1.0f - fClientY1)),
		rtSrc.left + rtSrc.right,
		rtSrc.top + (rtSrc.bottom*(1.0f - fOffestY1)) };

	m_Vertex[12] = { rt.left,
								rt.top + rt.bottom,
	rtSrc.left,
								rtSrc.top + rtSrc.bottom };
	m_Vertex[13] = { rt.left + (rt.right*fClientX0),
								rt.top + rt.bottom,
	rtSrc.left + (rtSrc.right*fOffestX0),
								rtSrc.top + rtSrc.bottom };
	m_Vertex[14] = { rt.left + (rt.right*(1.0f - fClientX1)),
								rt.top + rt.bottom,
	rtSrc.left + (rtSrc.right*(1.0f - fOffestX1)),
								rtSrc.top + rtSrc.bottom };
	m_Vertex[15] = { rt.left + rt.right,
								rt.top + rt.bottom,
	rtSrc.left + rtSrc.right,
								rtSrc.top + rtSrc.bottom };

	SetRect(0, m_Vertex[0], m_Vertex[1],
		m_Vertex[4], iBitmapID, iMaskBitmapID);
	SetRect(1, m_Vertex[1], m_Vertex[2],
		m_Vertex[5], iBitmapID, iMaskBitmapID);
	SetRect(2, m_Vertex[2], m_Vertex[3],
		m_Vertex[6], iBitmapID, iMaskBitmapID);

	SetRect(3, m_Vertex[4], m_Vertex[5],
		m_Vertex[8], iBitmapID, iMaskBitmapID);
	SetRect(4, m_Vertex[5], m_Vertex[6],
		m_Vertex[9], iBitmapID, iMaskBitmapID);
	SetRect(5, m_Vertex[6], m_Vertex[7],
		m_Vertex[10], iBitmapID, iMaskBitmapID);

	SetRect(6, m_Vertex[8], m_Vertex[9],
		m_Vertex[12], iBitmapID, iMaskBitmapID);
	SetRect(7, m_Vertex[9], m_Vertex[10],
		m_Vertex[13], iBitmapID, iMaskBitmapID);
	SetRect(8, m_Vertex[10], m_Vertex[11],
		m_Vertex[14], iBitmapID, iMaskBitmapID);
}

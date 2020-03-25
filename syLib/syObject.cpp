#include "syObject.h"
#include "syBitmapMgr.h"
#include "syInput.h"


syObject::syObject()
{
	m_fAlpha = 255.0f;
}


syObject::~syObject()
{
}

bool syObject::Load(std::wstring filename)
{
	int iKey = I_BitmapMgr.Load(filename);
	m_pBitmap = I_BitmapMgr.GetPtr(iKey);
	if (m_pBitmap == nullptr) return false;

	T_STR name = m_pBitmap->m_szPath;
	name += L"Mask_";
	name += m_pBitmap->m_szName;

	iKey = I_BitmapMgr.Load(name);
	m_pBitmapMask = I_BitmapMgr.GetPtr(iKey);

	return true;
}


bool syObject::Init()
{
	return true;
}


bool syObject::Frame()
{
	return true;
}

bool syObject::Render()
{

	if (m_pBitmapMask != nullptr)
	{
		m_pBitmapMask->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCAND);
	
		m_pBitmap->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCINVERT);
		m_pBitmapMask->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCINVERT);
	}
	else
	{
		m_pBitmap->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCCOPY);
	}
	return true;
}


bool syObject::Release()
{
	return true;
}

void syObject::SetColliRect(syPoint p, RECT rt)
{
	m_rtColl.left = p.x - (rt.right/ 2);
	m_rtColl.top = p.y - (rt.bottom/ 2);
	m_rtColl.right = rt.right + m_rtColl.left;
	m_rtColl.bottom = rt.bottom + m_rtColl.top;

	float fDistance = sqrt(
		(m_rtColl.right - m_rtColl.left) * (m_rtColl.right - m_rtColl.left)
		+
		(m_rtColl.bottom - m_rtColl.top) * (m_rtColl.bottom - m_rtColl.top));

	m_Sphere.vCenter = m_Pos;
	m_Sphere.fRadius = fDistance / 2;
}

void syObject::SetDrawRect(syPoint p, RECT rt)
{
	m_rtDraw.left = p.x - (rt.right / 2);
	m_rtDraw.top = p.y - (rt.bottom / 2);
	m_rtDraw.right = rt.right;
	m_rtDraw.bottom = rt.bottom;
	SetColliRect(p, rt);
}



void syObject::Set(syPoint pos, RECT rt, float fSpeed)
{
	m_rtObj = rt;
	m_fSpeed = fSpeed;
	SetPos(pos);
	
}
void     syObject::SetPos(POINT pos)
{
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	SetDrawRect(m_Pos, m_rtObj);
}
void     syObject::SetPos(syPoint pos)
{
	m_Pos = pos;
	SetDrawRect(m_Pos, m_rtObj);
}
void     syObject::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
	SetDrawRect(m_Pos, m_rtObj);
}


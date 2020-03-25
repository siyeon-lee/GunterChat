#pragma once
#include "syBitmap.h"


struct syObjectInfo
{
	syPoint		InitPos;
	int			iNumFrame;
	float		fTime;
	float		fLifeTime;
	int			iBitmapID;
	int			iMaskID;
	bool		bLoop;
	RECT		rtClient;
	float		fSpeed;

	std::vector<RECT> rtList;
	syObjectInfo() {
		iBitmapID = -1;
		iMaskID	= -1;
		bLoop = false;
	}
	syObjectInfo(syPoint p, RECT r, float f)
	{
		InitPos = p;
		rtClient = r;
		fSpeed = f;
		iBitmapID = -1;
		iMaskID = -1;
		bLoop = false;
	}
};


class syObject
{
public:
	syObject();
	virtual ~syObject();

public:
	syBitmap*   m_pBitmap;
	syBitmap*   m_pBitmapMask;
	syPoint		m_Pos;
	float		m_fSpeed;
public:
	RECT        m_rtDraw;
	RECT		m_rtObj;
	RECT        m_rtColl;
	sySphere	m_Sphere;
	float		m_fAlpha;
public:
	syBitmap*   GetBitmap() { return m_pBitmap; }
	syBitmap*   GetBitmapMask() { return m_pBitmapMask; }
	RECT		GetDrawRect() { return m_rtDraw; }
	RECT		GetCollRect() { return m_rtColl; }
	syPoint		GetPos() 	{	return m_Pos;	}
	float       GetSpeed() { return m_fSpeed; }
	void		SetSpeed(float sp) { m_fSpeed = sp; }
	void		SetPos(POINT pos);
	void		SetPos(syPoint pos);
	void		SetPos(float x, float y);

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

	virtual bool	Load(std::wstring filename);
	virtual void	SetDrawRect(syPoint p, RECT rt);
	virtual void	SetColliRect(syPoint p, RECT rt);
	virtual void	Set(syPoint pos, RECT rt, float fSpeed = 100.0f);
	virtual void	Set(syObjectInfo info)
	{
		m_Pos = info.InitPos;
		m_fSpeed = info.fSpeed;
		m_rtObj = info.rtClient;
		SetDrawRect(m_Pos, m_rtObj);
	}
};


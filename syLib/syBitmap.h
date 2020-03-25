#pragma once
#include "syStd.h"
class syBitmap
{
public:
	syBitmap();
	virtual ~syBitmap();

public:
	HBITMAP		m_hBitmap;
	HDC			m_hMemDC;
	T_STR		m_szName;
	T_STR		m_szPath;
	int			m_iIndex;
	BITMAP		m_BitmapInfo;
	float		m_fScale;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	bool    Load(std::wstring filename);
	bool    Draw(float x, float y, RECT rt, DWORD iMode = SRCCOPY);
	bool    Draw(float x, float y, RECT rt, BLENDFUNCTION bf);
	bool    Draw(RECT rtDesk, RECT rtSrc, BLENDFUNCTION bf);
	bool    Draw(RECT rtDesk, RECT rtSrc, DWORD iMode = SRCCOPY);
	bool    DrawColorKey(
		float x, float y, RECT rt, COLORREF color);
	void	setScale(float sc)
	{
		m_fScale = sc;
	};
};


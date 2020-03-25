#include "syBitmap.h"



syBitmap::syBitmap()
{
	m_fScale = 1;
}


syBitmap::~syBitmap()
{
}

bool syBitmap::Load(std::wstring filename)
{

	// API 파일입출력
	HANDLE hFile = CreateFile(filename.c_str(),
		GENERIC_READ, 0,
		NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	BITMAPFILEHEADER m_bitFileHeader;
	DWORD dwRead;
	ReadFile(hFile, &m_bitFileHeader,
		sizeof(BITMAPFILEHEADER), &dwRead, NULL);

	DWORD dwDataSize;
	dwDataSize = m_bitFileHeader.bfOffBits -
		sizeof(BITMAPFILEHEADER);
	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(dwDataSize);
	ReadFile(hFile, bitInfo,
		dwDataSize, &dwRead, NULL);

	PVOID pRaster = nullptr;
	m_hBitmap = CreateDIBSection(
		g_hScreenDC, bitInfo, DIB_RGB_COLORS, &pRaster, NULL, 0);
	ReadFile(hFile, pRaster,
		m_bitFileHeader.bfSize - m_bitFileHeader.bfOffBits,
		&dwRead, NULL);
	free(bitInfo);
	CloseHandle(hFile);


	m_hMemDC = CreateCompatibleDC(g_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
	return true;

}
bool    syBitmap::Draw(RECT rtDesk, RECT rtSrc, DWORD iMode)
{
	StretchBlt(g_hOffScreenDC,
		rtDesk.left, rtDesk.top,
		rtDesk.right, rtDesk.bottom,
		m_hMemDC,
		rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom,
		iMode);
	return true;
}

bool    syBitmap::Draw(RECT rtDesk, RECT rtSrc,
	BLENDFUNCTION bf)
{
	// DC -> DC
	AlphaBlend(g_hOffScreenDC,
		rtDesk.left, rtDesk.top,
		rtDesk.right, rtDesk.bottom,
		m_hMemDC,
		rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom,
		bf);
	return true;
}
bool syBitmap::Draw(float x, float y, RECT rt, DWORD iMode)
{

	//BitBlt(g_hOffScreenDC, x, y,
	//	rt.right, rt.bottom, m_hMemDC, rt.left, rt.top, iMode
	//);

	SetStretchBltMode(g_hOffScreenDC, HALFTONE);
	StretchBlt(g_hOffScreenDC, x, y,
		rt.right*m_fScale, rt.bottom*m_fScale,
		m_hMemDC, rt.left, rt.top, rt.right, rt.bottom,
		iMode);

	return true;
}
bool    syBitmap::Draw(float x, float y, RECT rt,
	BLENDFUNCTION bf)
{
	//factor = 0.75;
	// DC -> DC
	AlphaBlend(g_hOffScreenDC, x, y,
		rt.right*m_fScale,
		rt.bottom*m_fScale,
		m_hMemDC,
		rt.left, rt.top, rt.right, rt.bottom,
		bf);
	return true;
}
bool    syBitmap::DrawColorKey(
	float x, float y, RECT rt, COLORREF color)
{
	// DC -> DC
	TransparentBlt(
		g_hOffScreenDC, x, y, rt.right, rt.bottom,
		m_hMemDC, rt.left, rt.top, rt.right, rt.bottom,
		color);
	return true;
}

bool syBitmap::Init()
{
	return true;
}
bool syBitmap::Frame()
{
	return true;
}
bool syBitmap::Render()
{
	return true;
}
bool syBitmap::Release()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);	//오류시 지우시오
	return true;
}
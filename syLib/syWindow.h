#pragma once
#include "syStd.h"
class syWindow
{
public:
	HINSTANCE m_hInstance;
	HWND      m_hWnd;
	RECT      m_rtClient;
	RECT      m_rtWindow;
	DWORD     m_dwStyle;
public:
	bool		InitWindow(HINSTANCE hInstance, const TCHAR* pTitleName=0,
		int iX = 0, int iY = 0, int iWidth = 800, int iHeight = 600);
	bool		MyRegisterClass();
	void		CenterWindow();
	virtual LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	syWindow();
	virtual ~syWindow();
};


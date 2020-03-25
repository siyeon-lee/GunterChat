#include "syWindow.h"
HWND g_hWnd;
syWindow* g_pWindow = NULL;
HINSTANCE g_hInstance;
RECT      g_rtClient;

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pWindow != NULL)
	{
		g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
	}
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);// WM_QUIT 메세지큐 등록
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT		syWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParsssam)
{
	return 1;
}
bool syWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;
	wcex.lpfnWndProc = &WndProc;
	wcex.lpszClassName = L"KGCA";
	wcex.hInstance = m_hInstance;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEMOWINDOW);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	if (!RegisterClassExW(&wcex))
		return false;
	return true;
}
bool  syWindow::InitWindow(HINSTANCE hInstance, 
	const TCHAR* szTitleName,
	int iX, int iY, int iWidth, int iHeight)
{
	m_hInstance = hInstance;
	g_hInstance = m_hInstance;
	// 1) 윈도우 레지스터 등록
	if (MyRegisterClass() == false)
		return false;

	RECT rt = { 0,0, iWidth, iHeight };
	AdjustWindowRect(&rt, m_dwStyle, FALSE);

	// 2) 윈도우 생성
	//HWND hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
	m_hWnd = CreateWindow(
		L"KGCA",
		(szTitleName) ? szTitleName : L"siyeon's Window",
		//WS_POPUP | WS_SYSMENU,
		m_dwStyle,
		iX, iY,
		rt.right - rt.left,
		rt.bottom - rt.top, NULL, NULL,
		m_hInstance,
		NULL);
	if (m_hWnd == NULL) return 0;

	g_hWnd = m_hWnd;
	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	g_rtClient = m_rtClient;
	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
void syWindow::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}
syWindow::syWindow()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;
	g_pWindow = this;
}


syWindow::~syWindow()
{
}

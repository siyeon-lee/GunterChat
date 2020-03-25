#include "syCore.h"
HDC		 g_hOffScreenDC;
HDC		 g_hScreenDC;

bool syCore::Init()
{
	return true;
}
bool syCore::PreFrame()
{
	return true;
}

bool syCore::Frame()
{
	return true;
}
bool syCore::PostFrame()
{
	return true;
}


bool syCore::PreRender()
{
	PatBlt(m_hOffScreenDC,
		0, 0, 640,
		480, PATCOPY);
	return true;
}
bool syCore::Render()
{
	return true;
}
bool syCore::PostRender()
{
	if (m_bDebug == true)
	{
 		DebugRender();
	}
	// DC -> DC
	BitBlt(m_hScreenDC, 0, 0,
		640,
		480,
		m_hOffScreenDC,
		0,
		0, SRCCOPY);
	return true;
}
bool syCore::DebugRender()
{
	m_Timer.Render();
	I_Input.Render();
	I_SoundMgr.Render();
	return true;
}
bool syCore::Release()
{
	return true;
}
bool syCore::TCoreInit()
{

	m_hScreenDC = GetDC(m_hWnd);
	g_hScreenDC = m_hScreenDC;
	
	//더블버퍼링위해
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	g_hOffScreenDC = m_hOffScreenDC;

	m_bkColor = RGB(255, 255, 255);
	m_hbrBack = CreateSolidBrush(m_bkColor);
	SelectObject(m_hOffScreenDC, m_hbrBack);

	m_hPen = CreatePen(PS_SOLID, 0, RGB(255,0,0));
	
	int i = AddFontResource(L"SuperMario256.ttf");
	::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	m_fontDefault = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_DONTCARE, L"Super Mario 256");
	SelectObject(m_hOffScreenDC, m_fontDefault);


	m_Timer.Init();
	I_Input.Init();
	I_SoundMgr.Init();
	return Init();
}
bool syCore::TCoreFrame()
{
	DWORD CurrentTick = timeGetTime();
	DWORD delTick = CurrentTick - beforeTick;
	float tick = delTick / 1000.0f;

	//if (tick > 1/30)
	//{
	if (g_ActionInput.bSpace == KEY_PUSH)
	{
 		m_bDebug = !m_bDebug;
	}
	PreFrame();
		if(!m_Timer.Frame()) return false;
		I_Input.Frame();
		I_SoundMgr.Frame();
		beforeTick = CurrentTick;
		Frame();
	return PostFrame();
	/*}
	return false;*/
}
bool syCore::TCoreRender()
{
	PreRender();
	Render();
	PostRender();
	return true;
}
bool syCore::TCoreRelease()
{
	Release();
	DeleteObject(m_hPen);
	DeleteObject(m_fontDefault);
	DeleteObject(m_hOffScreenBitmap);
	DeleteObject(m_hbrBack);
	ReleaseDC(m_hWnd, m_hScreenDC);
	ReleaseDC(m_hWnd, m_hScreenDC);

	m_Timer.Release();
	I_Input.Release();
	I_SoundMgr.Release();
	return true;
}
void syCore::MessageProc(MSG msg)
{
	I_Input.MsgProc(msg);
}
bool syCore::Run()
{
	TCoreInit();
	MSG msg = { 0, };
	// WM_QUIT -> FALSE
	// 메세지 큐에서 하나하나씩 가져온다.
	//while (GetMessage(&msg, nullptr, 0, 0))
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 메세지 번역
			DispatchMessage(&msg);	// 메세지 프로시져 전달	
			MessageProc(msg);
		}
		else
		{
			// 게임로직
			TCoreFrame(); // 게임계산
			TCoreRender();// 게임드로우		
			//	Sleep(1);
		}
	}
	TCoreRelease(); // 게임 종료 
	return true;
}
syCore::syCore()
{
	m_bDebug = false;
}


syCore::~syCore()
{
}

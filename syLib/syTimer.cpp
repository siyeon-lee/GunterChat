#include "syTimer.h"
//__imp_timeGetTime 외부 기호 : winmm.lib
float g_fSecondPerFrame = 0.0f;
float g_fGameTimer = 0.0f;
bool       syTimer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
};
bool       syTimer::Frame()
{

	DWORD m_dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = m_dwCurrentTick - m_dwBeforeTick;
	DWORD dwInterval = 1000 / 60;
	LONG dwDelay = dwInterval - dwElapseTick;
	m_fSecondPerFrame = dwElapseTick / 1000.0f;
	
	if (dwDelay > 0)
	{
			
	/*		Sleep(dwDelay);
			dwElapseTick += dwDelay;*/
			return false;
	}
	//if (m_fSecondPerFrame > 1/60)
	//{
	//	m_fSecondPerFrame = 1/60;
	//}

	m_fAccumulation += m_fSecondPerFrame;
	m_fFrameTime += m_fSecondPerFrame;
	g_fSecondPerFrame = m_fSecondPerFrame;
	g_fGameTimer = m_fAccumulation;


	if (m_fFrameTime >= 1.0f)
	{
		m_iFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fFrameTime -= 1.0f;
		// 스트링버퍼에 출력해야 
		float tem = (float)1 / m_iFPS;
		_stprintf_s(m_csBuffer, _T("Timer:[%10.4f], FPS:[%d] 1/FPS:[%10.4f]"),
			m_fSecondPerFrame, m_iFPS, tem);
		//OutputDebugString(m_csBuffer);
	}
	m_dwFrameCount++;

	m_dwBeforeTick = m_dwCurrentTick;


	return true;
};
bool       syTimer::Render() {
	//HDC hdc = GetDC(g_hWnd);
	SetBkColor(g_hOffScreenDC, RGB(0, 0, 0));
	//SetTextColor(g_hOffScreenDC, RGB(255, 255, 255));
	SetTextColor(g_hOffScreenDC, RGB(255, 0, 0));
	SetBkMode(g_hOffScreenDC, TRANSPARENT);
	TextOut(g_hOffScreenDC, 0, 0, m_csBuffer, _tcslen(m_csBuffer));
	//ReleaseDC(g_hWnd, hdc);
	return true;
};
bool       syTimer::Release() {
	return true;
};

syTimer::syTimer()
{
	m_fSecondPerFrame = 0.0f; // 1프레임 경과시간
	m_fAccumulation = 0.0f; // 실행된 경과 시간
	m_iFPS = 0; // 1초에 진행된 프레임 카운터
	m_fFrameTime = 0.0f;
	m_dwFrameCount = 0;
}


syTimer::~syTimer()
{
}

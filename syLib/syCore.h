#pragma once
#include "syWindow.h"
#include "syTimer.h"
#include "syInput.h"
#include "sySoundMgr.h"

class syCore : public syWindow
{
	DWORD beforeTick = 0;
public:
	syTimer  m_Timer;
	bool	 m_bDebug;
	HDC		 m_hScreenDC;
	HDC		 m_hOffScreenDC;
	HBITMAP  m_hOffScreenBitmap;
	DWORD	 m_bkColor;
	HBRUSH	 m_hbrBack;
	HANDLE	 m_hPen;
	HFONT	 m_fontDefault;
public:
	virtual bool Init();
	virtual bool PreFrame();
	virtual bool Frame();
	virtual bool PostFrame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
	virtual bool DebugRender();

private:
	bool TCoreInit();
	bool TCoreFrame();
	bool TCoreRender();
	bool TCoreRelease();
	void MessageProc(MSG msg);
public:
	bool Run();
public:
	syCore();
	virtual ~syCore();
};


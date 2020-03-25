#pragma once
#include "syStd.h"



class syInput : public sySingleton<syInput>
{
	friend class sySingleton<syInput>;
private:
	DWORD m_dwKeyState[256];
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;
public:
	bool       Init();
	bool       Frame();
	bool       Render();
	bool       Release();
	DWORD      Key(DWORD dwKey);
	LRESULT		MsgProc(MSG msg);
	POINT		GetMousePos() {
		return m_MousePos;
	}
private:
	DWORD      KeyCheck(DWORD dwKey);
private:
	syInput();
public:
	virtual ~syInput();
};
#define I_Input syInput::GetInstance()

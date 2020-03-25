#pragma once
#include "syStd.h"
class syTimer
{
public:
	float     m_fSecondPerFrame; // 1������ ����ð�
	float     m_fAccumulation; // ����� ��� �ð�
	int       m_iFPS; // 1�ʿ� ����� ������ ī����
	DWORD	  m_dwBeforeTick;
	float     m_fFrameTime;
	DWORD     m_dwFrameCount;
	TCHAR     m_csBuffer[MAX_PATH];
public:
	bool       Init();
	bool       Frame();
	bool       Render();
	bool       Release();
public:
	syTimer();
	virtual ~syTimer();
};


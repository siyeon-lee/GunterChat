#pragma once
#include "Clientsample.h"
#include "syCore.h"
#include "GameScene.h"


//char username[] = "¿ÃΩ√ø¨";
//bool g_bChatting = false;
//bool g_bExit = false;
GameScene GS;
class sample : public syCore
{  
public:
	sample();
	~sample();
public:
	Clientsample client;
public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


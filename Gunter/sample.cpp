#pragma warning(disable:4996)
#include "sample.h"
#include <io.h>

sample::sample()
{
	int k = 0;
}


sample::~sample()
{
}

LRESULT		sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (WM_GAMEOVER == msg)
	{
		client.PostResult();
	}
	client.MsgProc(hWnd, msg, wParam, lParam);
	if (WM_UICONTRLMSG == msg || WM_GAMEOVER == msg)
	{
		GS.GameScene::MsgProc(hWnd, msg, wParam, lParam);
	}
	return 1;
}

bool   sample::Init()
{
	GS.Init();
	client.Init();
	return true;
}

bool   sample::Frame()
{

	client.PreFrame();
	GS.Frame();
	client.Frame();
	return true;
}

bool   sample::Render()
{
	GS.Render();
	client.PostRender();
	return true;
}

bool   sample::Release()
{
	GS.Release();
	client.Release();
	return true;
}

//syCORE_RUN(Gunter, 0, 0, 640, 480);
syCORE_RUN(Gunter, 0, 0, 1000, 600);
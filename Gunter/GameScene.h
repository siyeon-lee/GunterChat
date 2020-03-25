#pragma once
#include "syStd.h"
#include "syScene.h"
#include "background.h"
#include "syScriptManager.h"
#include "syPlayer.h"
#include "syEnemy.h"
#include "syFSM.h"
class GameScene 
{
public:
	GameScene();
	~GameScene();
public:
	syScene* m_pCurrentScene;
	syScene  m_LoginScene;
	syScene  m_LobbyScene;
	syScene  m_InGameScene;
	syScene	 m_EndingScene;
public:
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	syUIComponent  m_BaseControls;
	void  AddBaseControl();
	void    DefaultButtonControll();
public:
public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();
};


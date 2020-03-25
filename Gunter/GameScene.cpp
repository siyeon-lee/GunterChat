#include "GameScene.h"
#include "resource.h"

HWND g_hname;
TCHAR g_username[256] = {0,};
LRESULT CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
	{
		g_hname = GetDlgItem(hDlg, username);
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			GetWindowText(g_hname, (LPWSTR)g_username, sizeof(g_username));
			PostMessage(g_hWnd, WM_LOGIN_SUCCESS, 0, 0);
			EndDialog(hDlg, IDOK);
			return TRUE;
		}break;
		case IDCANCEL:
		{
			PostMessage(g_hWnd, WM_LOGIN_FAIL, 0, 0);
			MessageBox(NULL, L"로그인에 실패하였습니다", L"주의", MB_OK);
			
			return TRUE;
		}break;
		}
	}break;
	}
	return 0;
}

GameScene::GameScene()
{
	m_pCurrentScene = &m_LoginScene;
}


GameScene::~GameScene()
{
}
LRESULT		GameScene::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UINT msgControll = HIWORD(wParam);
	if (WM_LOGIN_SUCCESS == msgControll)
	{
		m_pCurrentScene = &m_LobbyScene;
	}
	if (WM_GAMESTART == msgControll)
	{
		if (m_pCurrentScene == &m_EndingScene)
		{
			GameScene::Release();
			GameScene::Init();
		}
		m_pCurrentScene = &m_InGameScene;
	}

	if (WM_GAMEOVER == msg)
	{
		m_pCurrentScene = &m_EndingScene;
	}

	return m_pCurrentScene->MsgProc(hWnd, msg, wParam, lParam);

}
void GameScene::DefaultButtonControll()
{
	int iNormal = I_BitmapMgr.Load(L"../../data/bitmap/main_start_nor.bmp");
	int iSelect = I_BitmapMgr.Load(L"../../data/bitmap/main_start_sel.bmp");
	int iPush = I_BitmapMgr.Load(L"../../data/bitmap/main_start_pus.bmp");
	int iDisable = I_BitmapMgr.Load(L"../../data/bitmap/main_start_dis.bmp");
	int iMaskBitmapID = -1;// I_BitmapMgr.Load(MaskPath.c_str());
	syButtonCtrl* pButton = new syButtonCtrl;
	syObjectInfo info;
	ZeroMemory(&info, sizeof(syObjectInfo));
	pButton->SetStateButton(iNormal, iSelect, iPush, iDisable, true);
	RECT rt = { 0, 0,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmWidth,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmHeight };
	info.InitPos = syPoint(299, 277);
	info.rtClient = rt;
	info.rtList.push_back(rt);
	pButton->Set(info, iNormal, iMaskBitmapID);
	m_BaseControls.Add(pButton);
}

void  GameScene::AddBaseControl()
{
	DefaultButtonControll();
	//DefalultListControll();
}

bool	GameScene::Init()
{
	g_score = 0;
	I_Fsm.Add(ACTION_MOVE, EVENT_DEAD, ACTION_DEAD);
	I_Fsm.Add(ACTION_DEAD, EVENT_FINDTARGET, ACTION_MOVE);
	//m_LoginScene
	DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, DlgProc);

	//m_LobbyScene
	AddBaseControl();
	int iBitmapID = I_BitmapMgr.Load(L"../../data/bitmap/gunter/startBK.bmp");
	int iMaskBitmapID = -1;// I_BitmapMgr.Load(MaskPath.c_str());

	syImgCtrl* pLobbyBk = new syImgCtrl();
	pLobbyBk->Init();
	
	syObjectInfo info;
	info.InitPos = syPoint(640/ 2, 480 / 2);
	RECT rt = { 0, 0, 640,480 };
	info.rtClient = rt;
	info.fSpeed = 0.0f;
	info.rtList.push_back(rt);
	pLobbyBk->Set(info, iBitmapID, iMaskBitmapID);
	m_LobbyScene.m_ctrlList.push_back(pLobbyBk);

	syButtonCtrl* pButton = (syButtonCtrl*)m_BaseControls.m_ctrlList[0]->Clone();
	pButton->m_iIndexType = 888;
	m_LobbyScene.m_ctrlList.push_back(pButton);
	m_pCurrentScene = &m_LobbyScene;


	//m_InGameScene 
	//배경 그리기
	m_InGameScene.Init();
	background* gamebk = new background();
	gamebk->Init();
	m_InGameScene.m_BackgruondList.push_back(gamebk->syBg);


	///권터 생성
	int Gunterdata = I_ScriptManager.Load(L"Text.txt");
	sySpriteData* pGunterSpriteData = I_ScriptManager.GetPtr(Gunterdata);
	for (auto &a : pGunterSpriteData->m_SpriteListData)
	{
		a.fSpeed = 100.0f;
	}
	syPlayer* m_gunter = new syPlayer;
	m_gunter->Init();
	m_gunter->m_bDead = false;
	m_gunter->m_iCurrentFrame = 0;
	m_gunter->Set(pGunterSpriteData->m_SpriteListData[GUNTER_JUMPINGFORWORD], pGunterSpriteData->m_iBitmapID, pGunterSpriteData->m_iMaskBitmapID);
	m_gunter->player_pos = pGunterSpriteData->m_SpriteListData[GUNTER_JUMPINGFORWORD].InitPos;
	m_gunter->SetrtFactor(0.5f);
	m_gunter->insertChar(pGunterSpriteData);
	m_InGameScene.m_playerList.push_back(m_gunter);

	//마리오 생성
	for (int i = 0; i <4; i++) 
	{
		int mariodata = I_ScriptManager.Load(L"mario.txt");
		sySpriteData* pmarioSpriteData = I_ScriptManager.GetPtr(mariodata);
		float mariospeed = rand() % 60 + 60;
		for (auto &a : pmarioSpriteData->m_SpriteListData)
		{
			a.fSpeed = mariospeed;
		}
		syEnemy* m_mario = new syEnemy;
		m_mario->Init();
		m_mario->m_bDead = false;
		m_mario->m_iCurrentFrame = 0;
		m_mario->Set(pmarioSpriteData->m_SpriteListData[MARIO_FORWORD], pmarioSpriteData->m_iBitmapID, pmarioSpriteData->m_iMaskBitmapID);
		m_mario->player_pos = syPoint(rand() % 300 + 300, 0);
		m_mario->insertChar(pmarioSpriteData);
		m_InGameScene.m_enemyList.push_back(m_mario);
	}

	//Ending Scene
	m_EndingScene.m_ctrlList.push_back(pLobbyBk);
	m_EndingScene.m_ctrlList.push_back(pButton);

	return true;
}

bool   GameScene::Frame()
{
	m_pCurrentScene->Frame();
	return true;
}

bool   GameScene::Render()
{
	m_pCurrentScene->Render();
	TCHAR     m_score[MAX_PATH];

	_stprintf_s(m_score, _T("%s:score[%d]"),
		g_username, g_score);


	SetBkColor(g_hOffScreenDC, RGB(0, 0, 0));
	SetTextColor(g_hOffScreenDC, RGB(255, 255, 255));
	SetBkMode(g_hOffScreenDC, TRANSPARENT);
	TextOut(g_hOffScreenDC, 0, 0, m_score, _tcslen(m_score));
	/*SelectObject(g_hOffScreenDC, oldfont);
	DeleteObject(font);*/
	return true;
}

bool   GameScene::Release()
{
	m_LoginScene.Release();
	m_LobbyScene.Release();
	m_InGameScene.Release();
	m_EndingScene.Release();
	return true;
}
#include "syScene.h"



syScene::syScene()
{
	m_bSceneChange = false;
}


syScene::~syScene()
{
}

bool syScene::Init()
{
	return true;
}

bool syScene::Frame()
{
	
	for (syUIComponent* data : m_ctrlList)
	{
		data->Frame();
	}
	for (syBackground& data : m_BackgruondList)
	{
		data.Frame();
	}
	for (syPlayer* data : m_playerList)
	{
		if (data->m_bDead)
		{
			std::vector<syPlayer*>::iterator it;
			for (it = m_playerList.begin(); it != m_playerList.end();)
			{
				if ((*it) == data)
				{
					it = m_playerList.erase(it);
					PostMessage(g_hWnd, WM_GAMEOVER, 0, 0);

				}
				else
				{
					it++;
				}
			}
			break;
		}
		for (syBackground& tiles : m_BackgruondList)
		{
			for (auto &tile : tiles.m_tiles)
			{
				//if (tile.second == -1) continue;
				if (data->syCharacter::setStand(tile.first)) break;
			}
		}
		data->Frame();
	}

	//몬스터
	for (syEnemy* data : m_enemyList)
	{
		////몬스터 삭제
		//if (data->m_bDead)
		//{
		//	std::vector<syEnemy*>::iterator it;
		//	for (it = m_enemyList.begin(); it != m_enemyList.end();)
		//	{
		//		if ((*it) == data)
		//		{
		//			it = m_enemyList.erase(it);
		//		}
		//		else
		//		{
		//			it++;
		//		}
		//	}
		//	break;
		//}		
		data->Frame();
		for (syBackground& tiles : m_BackgruondList)
		{
			for (auto &tile : tiles.m_tiles)
			{
				if (data->syCharacter::setStand(tile.first)) break;
			}
		}
		for (syPlayer* player : m_playerList)
		{
			data->ProcessAI(player);
		}
	}
	return true;
}

bool	syScene::Render()
{

	for (syUIComponent* data : m_ctrlList)
	{
		syListCtrl* pButton = (syListCtrl*)data;
		data->sySprite::Render();
		data->sySprite::Draw(SRCCOPY);
	}
	for (syBackground& data : m_BackgruondList)
	{
		data.Render();
	}
	for (syPanel& data : m_PanelList)
	{
		data.Draw(SRCCOPY);
	}
	for (syPlayer* data : m_playerList)
	{
		data->Render();
	}
	for (syEnemy* data : m_enemyList)
	{
		data->Render();
	}
	return true;
}

bool syScene::Release()
{
	for (syPanel& data : m_PanelList)
	{
		data.Release();
		m_PanelList.pop_back();
	}

	for (syUIComponent* data : m_ctrlList)
	{
		data->Release();
		m_ctrlList.pop_back();
	}
	for (syPlayer* data : m_playerList)
	{
		data->Release();
		m_playerList.pop_back();
	}
	for (syEnemy* data : m_enemyList)
	{
		data->Release();
		m_enemyList.pop_back();
	}
	for (syBackground &data : m_BackgruondList)
	{
		data.Release();
		m_BackgruondList.pop_back();
	}
	return true;
}




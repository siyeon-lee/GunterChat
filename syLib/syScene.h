#pragma once
#include "syPanel.h"
#include "syBackground.h"
#include "syPlayer.h"
#include "syEnemy.h"
class syScene : public syUIComponent
{
public:
	syScene();
	virtual ~syScene();
public:
	std::vector<syPanel>   m_PanelList;
	std::vector<syBackground>   m_BackgruondList;
	std::vector<syPlayer*>	m_playerList;
	std::vector<syEnemy*>	m_enemyList;
	//std::vector<syCharacter*> m_charList;
	
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool IsSceneChange()
	{
		if (m_bSceneChange)
		{
			return true;
		}
		return false;
	};

};


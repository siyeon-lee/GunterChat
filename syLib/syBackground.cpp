#include "syBackground.h"



syBackground::syBackground()
{
}


syBackground::~syBackground()
{
}

bool  syBackground::Frame()
{
	for (auto &data : m_tiles)
	{
		data.first->Frame();
	}
	return true; 
}

bool  syBackground::Render()
{
	m_backgrounds.Render();
	for (auto &a : m_tiles)
	{
		a.first->Render();
	}

	return true;
}

bool  syBackground::Release()
{
	for (auto &a : m_tiles)
	{
		delete(a.first);

	}
	m_tiles.clear();
	m_backgrounds.Release();
	return true;
}

void  syBackground::insertTiles(sySprite* pBk, int tilevaule)
{
	m_tiles.insert(pair<sySprite*, int>(pBk, tilevaule));
}

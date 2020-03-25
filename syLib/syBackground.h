#pragma once
#include "syStd.h"
#include "syUIComponent.h"
class syBackground : public syUIComponent
{
public:
	syBackground();
	virtual ~syBackground();
public:
	std::map<sySprite*, int>		m_tiles;
	syObject	m_backgrounds;
public:
	bool  Frame();
	bool  Render();
	bool  Release();
	void  insertTiles(sySprite* pBk, int tilevaule);

};


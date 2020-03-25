#pragma once
#include "syListCtrl.h"
#include "syImgCtrl.h"
class syPanel : public syUIComponent
{
public:
	syPanel();
	virtual ~syPanel();
public:
	std::vector<syPanel>	m_PanelList;
public:
	bool Render();
	bool Release();
};


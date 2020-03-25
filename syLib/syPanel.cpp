#include "syPanel.h"



syPanel::syPanel()
{
}

syPanel::~syPanel()
{
}

bool syPanel::Render()
{
	for (syPanel& data : m_PanelList)
	{
		data.Draw(SRCCOPY);
	}
	return true;
}

bool syPanel::Release()
{
	for (syPanel& data : m_PanelList)
	{
		data.Release();
	}
	return true;
}
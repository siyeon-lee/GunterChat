#pragma once
#include "syNetwork.h"

class Clientsample
{
public:
	Clientsample();
    virtual	~Clientsample();
private:
	
public:
	bool		Init();
	bool		PreFrame();
	bool		Frame();
	bool		PostRender();
	bool		Release();
	bool		PacketProcess();
	bool		PostResult();
public:
	//LRESULT myEditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


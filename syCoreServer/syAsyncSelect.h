#pragma once
#include "sySelectModel.h"
class syAsyncSelect : public sySelectModel
{
public:
	syAsyncSelect(SOCKET sock);
	virtual ~syAsyncSelect();
public:
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool		Init();
};


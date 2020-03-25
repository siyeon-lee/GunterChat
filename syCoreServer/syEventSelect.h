#pragma once
#include "sySelectModel.h"
class syEventSelect : public sySelectModel
{
public:
	syEventSelect(SOCKET sock);
	virtual ~syEventSelect();
public:
	HANDLE		m_EventArray[64];
public:
	bool		Init();
	bool		Frame();
};



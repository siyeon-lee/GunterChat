#pragma once
#include "sySelectModel.h"
class syStdSelect : public sySelectModel
{
public:
	syStdSelect(SOCKET sock);
	virtual ~syStdSelect();
public:
	FD_SET  rSet;
	FD_SET  wSet;
public:
	virtual bool	Init();
	virtual bool	Frame();
};


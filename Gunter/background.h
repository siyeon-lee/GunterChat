#pragma once
#include "syBackground.h"
class background
{
public:
	background();
	virtual ~background();
public:
	syBackground syBg;
public:
	void	drawtileRect();
public:
	bool   Init();
};
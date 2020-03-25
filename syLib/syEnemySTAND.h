#pragma once
#include "syEnemyState.h"
class syEnemySTAND : public syEnemyState
{
public:
	syEnemySTAND(syEnemy* pParent);
	virtual ~syEnemySTAND();
public:
	void Process(syCharacter* pTarget);
};


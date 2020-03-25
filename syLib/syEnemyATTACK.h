#pragma once
#include "syEnemyState.h"
class syEnemyATTACK : public syEnemyState
{
public:
	syEnemyATTACK(syEnemy* pParent);
	virtual ~syEnemyATTACK();
public:
	void Process(syCharacter* pTarget);
};


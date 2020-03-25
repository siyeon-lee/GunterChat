#pragma once
#include "syEnemyState.h"
class syEnemyDEAD : public syEnemyState
{
public:
	syEnemyDEAD(syEnemy* pParent);
	virtual ~syEnemyDEAD();
public:
	void Process(syCharacter* pTarget);
};


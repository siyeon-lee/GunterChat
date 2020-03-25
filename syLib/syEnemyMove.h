#pragma once
#include "syEnemyState.h"
class syEnemyMove : public syEnemyState
{
public:
	syEnemyMove(syEnemy* pParent);
	virtual ~syEnemyMove();


public:
	void Process(syCharacter* pTarget);
};


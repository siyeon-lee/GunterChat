#pragma once
#include "syCharacter.h"
#include "syFiniteState.h"
class syEnemy;
class syEnemyState
{
public:
	syEnemyState(syEnemy* pParent) : m_pOwner(pParent) {}
	virtual ~syEnemyState();
public:
	syEnemy* m_pOwner;
public:
	virtual void Process(syCharacter* pTarget) = 0;

};


#pragma once
#include "syStd.h"
#include "syUIComponent.h"
#include "syBackground.h"
#include "syCharacter.h"

enum syBITMAPGUNTER
{
	GUNTER_FORWORD,
	GUNTER_BACKWORD,
	GUNTER_LANDINGFORWORD,
	GUNTER_LANDINGBACKWORD,
	GUNTER_JUMPINGFORWORD,
	GUNTER_JUMPINGBACKWORD,
	GUNTER_IDLEFORWORD,
	GUNTER_IDLEBACKWORD
};

class syPlayer : public syCharacter
{

public:
	syPlayer();
	virtual ~syPlayer();
public:
	bool  Frame();
	//bool  Render();
	//bool  Release();
	//void  insertHero(syCharacter* pHero, sySpriteData* pGunter);
	//void  SetSpriteBitmap(int spriteNum);
	//void  setStand(syBackground* tiles);
};

#pragma once
#include "syCollision.h"
#include "sySprite.h"
class syCharacter : public sySprite
{
public:
	syCharacter();
	virtual ~syCharacter();
public:
	sySpriteData*				pSpriteData;
	float						ySpeed = 0.0f;
	bool						isStand = false;
	int							spritenum = 0;
	bool						isFront = true;
	syPoint						player_pos;
	float						m_rtFactor = 1.0f;
	float						YSPEED = 200.0f;
public:
	bool Frame();
	bool Render();
	bool setStand(sySprite* tile);
	bool  Release();
	void  insertChar(sySpriteData* pGunter);
	void  SetSpriteBitmap(int spriteNum);
	void SetrtFactor(float factor)
	{
		m_rtFactor = factor;
	};
	void SetYSPEED(float y)
	{
		YSPEED = y;
		ySpeed = YSPEED;
	};

};
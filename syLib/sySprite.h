#pragma once
#include "syObject.h"
#include "syBitmapMgr.h"
#include "syScriptManager.h"
class sySprite : public syObject
{
public:
	syObjectInfo m_info;
	float		m_fDeltaTime;// = 3.0f / iNumSprite;
	bool		m_bDead;
	int			m_iSpriteID;
	int			m_iCurrentFrame;
	float       m_fTmpTime;
	bool		m_bSceneChange;

public:
	bool  Init();
	bool  Frame();
	bool  Render();
	bool  Release();
	virtual bool  Set(syObjectInfo info, int bitmapid, int mask);
	virtual void  Draw(DWORD dwMode);
	void  Draw(int x, int y, DWORD dwMode);
	void  DrawCenter(DWORD dwMode);
public:
	sySprite();
	virtual ~sySprite();
};


#pragma once
#include "syUIComponent.h"
class syButtonCtrl : public syUIComponent
{
public:
	syButtonCtrl();
	virtual ~syButtonCtrl();
public:
	bool m_bCollision;
	int m_iNormal;
	int m_iHover;
	int m_iPush;
	int m_iDisable;
	bool m_bSelect;
	syBitmap*  m_pCurrentBitmap;
	syBitmap*  m_pStateBitmap[4];

public:
	syUIComponent* Clone();
	void SetStateButton(int nor, int sel, int pus, int dis, bool coll = false);
	virtual void Draw(DWORD dwMode) override;
	bool Set(syObjectInfo info, int id, int mask);
	bool  Frame();
	bool  Release();

};


#pragma once
#include "syStd.h"
class syCollision
{
public:
	syCollision();
	~syCollision();

public:
	static bool RectInPt(RECT rt, POINT pt);
	static bool RectInPt(RECT rt, syPoint pt);
	static bool RectInRect(RECT rt1, RECT rt2);

	static bool SphereInSphere(RECT rt1, RECT rt2);

	static bool SphereInPoint(sySphere rt, POINT pos);
	static bool SphereInPoint(sySphere rt, syPoint pos);
};


#pragma once
#include "syButtonCtrl.h"
class syListCtrl : public syButtonCtrl
{
public:
	syListCtrl();
	virtual ~syListCtrl();

public:
	std::vector<syButtonCtrl> m_btnList;
	int m_iStart;
	int m_iEnd;
	int m_iSubButtonHeight; // 서브 버튼의 세로 크기
	int m_iOffsetBaseX; // 부모의 시작위치로 부터 떨어진 거리
	int m_iOffsetBaseY;
	int m_iButtonStep;
public:
	void SetAttribute(
		int iSubButtonHeight, // 서브 버튼의 세로 크기
		int iOffsetBaseX, // 부모의 시작위치로 부터 떨어진 거리
		int iOffsetBaseY,
		int  iButtonStep);
	syUIComponent* Clone();
	virtual void  Draw(DWORD dwMode) override;
	bool Frame();
	bool Release();
};

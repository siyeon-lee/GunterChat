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
	int m_iSubButtonHeight; // ���� ��ư�� ���� ũ��
	int m_iOffsetBaseX; // �θ��� ������ġ�� ���� ������ �Ÿ�
	int m_iOffsetBaseY;
	int m_iButtonStep;
public:
	void SetAttribute(
		int iSubButtonHeight, // ���� ��ư�� ���� ũ��
		int iOffsetBaseX, // �θ��� ������ġ�� ���� ������ �Ÿ�
		int iOffsetBaseY,
		int  iButtonStep);
	syUIComponent* Clone();
	virtual void  Draw(DWORD dwMode) override;
	bool Frame();
	bool Release();
};

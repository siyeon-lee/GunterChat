#pragma once
#include "syBitmap.h"
class syBitmapMgr : public sySingleton<syBitmapMgr>
{

	friend class sySingleton<syBitmapMgr>;
	typedef std::map<int, syBitmap*>::iterator ITOR;
	// 사전식 컨테이너 < 키, 값 >
	std::map<int, syBitmap*>   m_List;

public:
	int					m_iNumBitmap;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int         Load(T_STR filepath);
	syBitmap*		GetPtr(int iKey);
	bool		Delete(int iKey);
private:
	syBitmapMgr();
public:
	~syBitmapMgr();
};


#define I_BitmapMgr syBitmapMgr::GetInstance()

#pragma once
#include "syBitmap.h"
class syBitmapMgr : public sySingleton<syBitmapMgr>
{

	friend class sySingleton<syBitmapMgr>;
	typedef std::map<int, syBitmap*>::iterator ITOR;
	// ������ �����̳� < Ű, �� >
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

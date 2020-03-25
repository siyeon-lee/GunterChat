#include "syBitmapMgr.h"



syBitmapMgr::syBitmapMgr()
{
	m_iNumBitmap = 0;
}


syBitmapMgr::~syBitmapMgr()
{
	Release();
}


bool		syBitmapMgr::Init()
{
	return true;
}

bool		syBitmapMgr::Frame()
{
	return true;
}

bool		syBitmapMgr::Render()
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		syBitmap* pBitmap = (*itor).second;
		pBitmap->Render();
	}
	return true;
}

bool		syBitmapMgr::Release()
{
	for (ITOR itor = m_List.begin();itor != m_List.end();)
	{
		syBitmap* pBitmap = (*itor).second;
		pBitmap->Release();
		delete pBitmap;
		itor = m_List.erase(itor);
	}

	m_List.clear();
	return true;
}

syBitmap*		syBitmapMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);

	if (itor != m_List.end())
	{
		syBitmap* pData = (*itor).second;
		return pData;
	}
	return nullptr;
}

bool		syBitmapMgr::Delete(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		syBitmap* pData = (*itor).second;
		pData->Release();
		delete pData;
		m_List.erase(itor);
		return true;
	}
	return false;
}




int        syBitmapMgr::Load(T_STR filepath)
{
	//path split
	if (filepath.empty()) return -1;

	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(filepath.c_str(), Drive, Dir, Name, Ext);

	T_STR filename = Name;
	filename += Ext;

	T_STR path = Drive;
	path += Dir;

	// 중복제거
	for (ITOR itor = m_List.begin(); itor != m_List.end();itor++)
	{
		syBitmap* pData = (*itor).second;
		if (pData->m_szName == filepath)
		{
			return pData->m_iIndex;
		}
	}
	syBitmap* pData = new syBitmap;
	if (pData->Load(filepath) == false)
	{
		delete pData;
		return -1;
	}
	pData->m_szName = filename;
	pData->m_szPath = path;
	pData->m_iIndex = m_iNumBitmap++;
	m_List.insert(make_pair(pData->m_iIndex, pData));
	return pData->m_iIndex;
}


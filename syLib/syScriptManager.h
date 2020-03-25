#pragma once
#include "syObject.h"

struct sySpriteData
{
	T_STR	m_szPath;
	T_STR	m_szName;
	int		m_iIndex;
	int     m_iBitmapID;
	int     m_iMaskBitmapID;
	std::vector<syObjectInfo>   m_SpriteListData;
};
class syScriptManager : public sySingleton<syScriptManager>
{
	friend class sySingleton<syScriptManager>;
	typedef std::map<int, sySpriteData>::iterator ITOR;
	std::map<int, sySpriteData>   m_list;
	int			m_iIndex;
public:
	int     Load(const TCHAR* pFileName);
	bool	GameDataLoad(T_STR name, sySpriteData& data);
	sySpriteData*  GetPtr(int iKey);
	bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();

private:
	syScriptManager();
public:
	virtual ~syScriptManager();
};

#define I_ScriptManager syScriptManager::GetInstance()

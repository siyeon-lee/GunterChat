#include "syScriptManager.h"
#include "syBitmapMgr.h"


syScriptManager::syScriptManager()
{
	m_iIndex = 0;
}


syScriptManager::~syScriptManager()
{
}

bool syScriptManager::GameDataLoad(T_STR name, sySpriteData& data)
{
	FILE* fp = 0;
	_wfopen_s(&fp, name.c_str(), _T("rt"));
	if (fp == NULL) return false;

	TCHAR buffer[256] = { 0, };
	TCHAR temp[256] = { 0, };
	TCHAR bitmap[256] = { 0, };
	TCHAR mask[256] = { 0, };
	int iNumSprite = -1;

	_fgetts(buffer, _countof(buffer), fp);
	_stscanf_s(buffer, _T("%s%d%s%s"),
		temp, _countof(temp),
		&iNumSprite,
		bitmap, _countof(bitmap),
		mask, _countof(mask));

	T_STR path = L"../../data/bitmap/";
	T_STR BitmapPath = path + bitmap;
	T_STR MaskPath = path + mask;
	data.m_iBitmapID = I_BitmapMgr.Load(BitmapPath.c_str());
	data.m_iMaskBitmapID = I_BitmapMgr.Load(MaskPath.c_str());

	data.m_SpriteListData.resize(iNumSprite);

	int iNumFrame = -1;
	for (int iSprite = 0; iSprite < iNumSprite; iSprite++)
	{
		//TObjectInfo info;
		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d%f%f%f%f%s%s"),
			temp, _countof(temp),
			&data.m_SpriteListData[iSprite].iNumFrame,
			&data.m_SpriteListData[iSprite].InitPos.x,
			&data.m_SpriteListData[iSprite].InitPos.y,
			&data.m_SpriteListData[iSprite].fTime,
			&data.m_SpriteListData[iSprite].fLifeTime,
			bitmap, _countof(bitmap),
			mask, _countof(mask));

		if (_tcscmp(bitmap, L"null"))
		{
			BitmapPath.clear();
			BitmapPath = path + bitmap;
			data.m_SpriteListData[iSprite].iBitmapID = I_BitmapMgr.Load(BitmapPath.c_str());
		}
		if (_tcscmp(mask, L"null"))
		{
			MaskPath.clear();
			MaskPath = path + bitmap;
			data.m_SpriteListData[iSprite].iMaskID = I_BitmapMgr.Load(MaskPath.c_str());
		}
		data.m_SpriteListData[iSprite].rtList.resize(
			data.m_SpriteListData[iSprite].iNumFrame);

		int iCount = -1;
		for (int iCnt = 0; iCnt < data.m_SpriteListData[iSprite].iNumFrame; iCnt++)
		{
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%d%d%d%d%d"),
				&iCount,
				&data.m_SpriteListData[iSprite].rtList[iCnt].left,
				&data.m_SpriteListData[iSprite].rtList[iCnt].top,
				&data.m_SpriteListData[iSprite].rtList[iCnt].right,
				&data.m_SpriteListData[iSprite].rtList[iCnt].bottom);
		}
	}
	fclose(fp);
	return true;
}

int   syScriptManager::Load(const TCHAR* pFileName)
{
	sySpriteData data;
	if (GameDataLoad(pFileName, data))
	{
		data.m_iIndex = m_iIndex;
		data.m_szName = pFileName;
		m_list.insert(make_pair(m_iIndex++, data));
	}
	return m_iIndex - 1;
}

sySpriteData*  syScriptManager::GetPtr(int iKey)
{
	ITOR itor = m_list.find(iKey);
	if (itor == m_list.end())
	{
		return NULL;
	}
	sySpriteData* data = &(*itor).second;
	return data;
}
bool   syScriptManager::Init() {
	return true;
}
bool   syScriptManager::Frame() {
	return true;
}
bool   syScriptManager::Render() {
	return true;
}
bool   syScriptManager::Release() {
	return true;
}


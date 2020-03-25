#include "sySoundMgr.h"
//std::vector<sySound*>   m_List; front<->back push
//std::list<sySound*>   m_List;   front<->back push
//std::set<sySound*>   m_List;    front<->back push
// 리스트 관리-> 검색 최적화 stl
// 기본저장 방식 -> BST -> 0,1,2 -> find
//std::map<DWORD, sySound*>   m_List;
//std::map<string, sySound*>   m_List;
// m_List["홍길동"] = pSound;
bool		sySoundMgr::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	I_SoundMgr.Load(L"../../data/sound/mario.mp3");
	I_SoundMgr.Load(L"../../data/sound/Jump.wav");
	I_SoundMgr.Load(L"../../data/sound/Mariodies.wav");
	I_SoundMgr.Load(L"../../data/sound/Gameover.mp3");
	I_SoundMgr.Load(L"../../data/sound/win.wav");

	return true;
}
void		sySoundMgr::Play(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		sySound* pSound = (*itor).second;
		pSound->Play();
	}
}
sySound*		sySoundMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		sySound* pSound = (*itor).second;
		return pSound;
	}
	return nullptr;
}
bool		sySoundMgr::Delete(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		sySound* pSound = (*itor).second;
		pSound->Release();
		delete pSound;
		m_List.erase(itor);
		return true;
	}
	return false;
}
bool		sySoundMgr::Render()
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		sySound* pSound = (*itor).second;
		pSound->Render();
	}
	return true;
};

int        sySoundMgr::Load(T_STR pSoundFile)
{
	if (pSoundFile.empty()) return -1;
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(pSoundFile.c_str(),
		Drive, Dir, Name, Ext);

	T_STR filename = Name;
	filename += Ext;

	T_STR path = Drive;
	path += Dir;


	// 중복제거
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		sySound* pSound = (*itor).second;
		if (pSound->m_szName == filename)
		{
			return pSound->m_iIndex;
		}
	}

	C_STR filepath = wtm(pSoundFile);
	sySound* pSound = new sySound;
	FMOD_RESULT ret = m_pSystem->createSound(
		filepath.c_str(),
		FMOD_DEFAULT, 0, &pSound->m_pSound);
	if (ret != FMOD_OK)
	{
		delete pSound;
		return -1;
	}
	pSound->m_pSystem = m_pSystem;
	pSound->m_szName = filename;
	pSound->m_szPath = path;
	pSound->m_iIndex = m_iNumSound++;
	//1)
	//m_List[pSound->m_iIndex] = pSound;	
	//2)
	m_List.insert(make_pair(pSound->m_iIndex, pSound));
	return pSound->m_iIndex;
}


bool		sySoundMgr::Frame()
{
	m_pSystem->update();
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		sySound* pSound = (*itor).second;
		pSound->Frame();
	}

	return true;
};

bool		sySoundMgr::Release()
{
	//1)
	for (ITOR itor = m_List.begin();itor != m_List.end();)
	{
		sySound* pSound = (*itor).second;
		pSound->Release();
		delete pSound;
		itor = m_List.erase(itor);
	}
	//2)
	/*for (int iSound = 0; iSound < g_iMaxSound; iSound++)
	{
		sySound* pSound = m_List[iSound];
		pSound->Release();
		delete pSound;
	}*/
	m_List.clear();

	m_pSystem->close();
	m_pSystem->release();
	return true;
};

sySoundMgr::sySoundMgr()
{
	m_iNumSound = 0;
	m_fVolume = 0.5f;
}


sySoundMgr::~sySoundMgr()
{
}

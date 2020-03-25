#pragma once
// ../../FMOD/inc      fmod.hpp
// ../../FMOD/lib/x64  fmod_vc.lib
// fmod.dll  현재 폴더 및 실행파일 위치

#include "sySound.h"

const int g_iMaxSound = 10;

class sySoundMgr : public sySingleton<sySoundMgr>
{
	friend class sySingleton<sySoundMgr>;
	typedef std::map<int, sySound*>::iterator ITOR;
	// 사전식 컨테이너 < 키, 값 >
	std::map<int, sySound*>   m_List;
public:
	FMOD::System*		m_pSystem;
	float				m_fVolume;
	int					m_iNumSound;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int         Load(T_STR pFilePath);
	sySound*	GetPtr(int iKey);
	bool		Delete(int iKey);
	void		Play(int dwKey);
private:
	sySoundMgr();
public:
	~sySoundMgr();
};
#define I_SoundMgr sySoundMgr::GetInstance()

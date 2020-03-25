#pragma once
#include "syStd.h"
#include <map>
#include <string>
#include "fmod.hpp"
using namespace std;

class sySound
{
public:
	FMOD::System*		m_pSystem;
	T_STR				m_szPath;
	T_STR				m_szName;
	int					m_iIndex;
public:
	FMOD::Sound*		m_pSound;
	int					m_iNumSound;
	float				m_fVolume;
	FMOD::Channel*      m_pChannel;
	std::string         m_csBuffer;
public:
	void		Play();
	void		Stop();
	void        Paused();
	void        Volume(float fVolume = 1.0f, bool bUp = true);
	void        PlayEffect();
	void		SetMode(DWORD dwMode);
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
public:
	sySound();
	virtual ~sySound();
};
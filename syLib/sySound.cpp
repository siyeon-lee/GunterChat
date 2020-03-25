#include "sySound.h"
void		sySound::Play()
{
	bool playing = false;
	if (m_pChannel)
	{
		m_pChannel->isPlaying(&playing);
	}
	if (playing == false)
	{
		m_pSystem->playSound(m_pSound, 0, false, &m_pChannel);
		m_pChannel->setVolume(m_fVolume);
	}
}
void		sySound::SetMode(DWORD dwMode)
{
	if (m_pChannel)
	{
		m_pChannel->setMode(dwMode);
	}
}
void		sySound::Stop()
{
	if (m_pChannel)
	{
		m_pChannel->stop();
	}
}
void		sySound::Paused()
{
	if (m_pChannel == nullptr) return;
	bool paused;
	m_pChannel->getPaused(&paused);
	m_pChannel->setPaused(!paused);
}
void        sySound::Volume(float fVolume, bool bUp)
{
	if (m_pChannel == nullptr) return;
	float fCurrentVolume;
	m_pChannel->getVolume(&fCurrentVolume);
	if (bUp == true)
	{
		fCurrentVolume += fVolume * g_fSecondPerFrame * 10.0f;
		fCurrentVolume = min(1.0f, fCurrentVolume);
	}
	else
	{
		fCurrentVolume -= fVolume * g_fSecondPerFrame* 10.0f;
		fCurrentVolume = max(0.0f, fCurrentVolume);
	}

	m_pChannel->setVolume(fCurrentVolume);
}
void        sySound::PlayEffect()
{
	FMOD::Channel* pChannel = nullptr;
	pChannel->setVolume(m_fVolume);
	pChannel->setMode(FMOD_LOOP_OFF);

	m_pSystem->playSound(m_pSound, 0, false, &pChannel);
}
bool	sySound::Init()
{
	return true;
}
bool	sySound::Frame()
{
	return true;
}
bool	sySound::Render()
{
	return true;
}
bool	sySound::Release()
{
	if (m_pSound == nullptr) return false;
	m_pSound->release();
	return true;
}

sySound::sySound()
{
	m_fVolume = 0.5f;
	m_pChannel = nullptr;
	m_pSound = nullptr;
}


sySound::~sySound()
{
}

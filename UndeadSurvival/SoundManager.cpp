#include "pch.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Sound.h"

SoundManager::~SoundManager()
{
	if (m_pDirectSound)
		m_pDirectSound->Release();
}

void SoundManager::Init(HWND hwnd)
{
	// 사운드 디바이스 생성
	if (FAILED(DirectSoundCreate(NULL, &m_pDirectSound, NULL)))
	{
		MessageBox(hwnd, L"사운드디바이스생성실패", L"Error", MB_OK);
		return;
	}

	// 사운드 디바이스 초기화
	if (FAILED(m_pDirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
	{
		MessageBox(hwnd, L"사운드디바이스초기화실패", L"Error", MB_OK);
		return;
	}
}

void SoundManager::Play(const wstring& name, bool loop)
{
	Sound* sound = GET_SINGLE(ResourceManager)->GetSound(name);
	
	if (!sound) return;

	sound->Play(loop);
}
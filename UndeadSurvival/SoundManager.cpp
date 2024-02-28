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
	// ���� ����̽� ����
	if (FAILED(DirectSoundCreate(NULL, &m_pDirectSound, NULL)))
	{
		MessageBox(hwnd, L"�������̽���������", L"Error", MB_OK);
		return;
	}

	// ���� ����̽� �ʱ�ȭ
	if (FAILED(m_pDirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
	{
		MessageBox(hwnd, L"�������̽��ʱ�ȭ����", L"Error", MB_OK);
		return;
	}
}

void SoundManager::Play(const wstring& name, bool loop)
{
	Sound* sound = GET_SINGLE(ResourceManager)->GetSound(name);
	
	if (!sound) return;

	sound->Play(loop);
}
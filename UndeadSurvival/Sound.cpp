#include "pch.h"
#include "Sound.h"
#include "SoundManager.h"

Sound::Sound()
{

}

Sound::~Sound()
{
	if(m_soundBuffer) m_soundBuffer->Release();
}

bool Sound::LoadWave(fs::path fullPath)
{
	if(fullPath.empty()) return false;
	if(fullPath.extension() != ".wav") return false;

	HMMIO file = mmioOpen((WCHAR*)fullPath.c_str(), nullptr, MMIO_READ | MMIO_ALLOCBUF);
	if (!file) 
	{
		MessageBox(NULL, L"사운드 파일 없음", L"", MB_OK);
		return false;
	}

	MMCKINFO parent;
	::memset(&parent, 0, sizeof(parent));
	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	::mmioDescend(file, &parent, NULL, MMIO_FINDRIFF);

	MMCKINFO child;
	::memset(&child, 0, sizeof(child));
	child.ckid = mmioFOURCC('f', 'm', 't', ' ');
	::mmioDescend(file, &child, &parent, MMIO_FINDCHUNK);

	WAVEFORMATEX wft;
	::memset(&wft, 0, sizeof(wft));
	::mmioRead(file, (char*)&wft, sizeof(wft));

	::mmioAscend(file, &child, 0);
	child.ckid = mmioFOURCC('d', 'a', 't', 'a');
	::mmioDescend(file, &child, &parent, MMIO_FINDCHUNK);

	::memset(&m_bufferDesc, 0, sizeof(DSBUFFERDESC));
	m_bufferDesc.dwBufferBytes = child.cksize;
	m_bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	m_bufferDesc.dwFlags = DSBCAPS_STATIC;
	m_bufferDesc.lpwfxFormat = &wft;

	if (FAILED(GET_SINGLE(SoundManager)->GetDirectSound()->CreateSoundBuffer(&m_bufferDesc, &m_soundBuffer, NULL)))
	{
		::MessageBox(NULL, L"사운드 버퍼 생성 실패", L"", MB_OK);
		return false;
	}

	void* write1 = NULL;
	void* write2 = NULL;
	DWORD len1;
	DWORD len2;

	m_soundBuffer->Lock(0, child.cksize, &write1, &len1, &write2, &len2, 0);

	if (write1)
		::mmioRead(file, (char*)write1, len1);

	if (write2)
		::mmioRead(file, (char*)write2, len2);

	m_soundBuffer->Unlock(write1, len1, write2, len2);

	::mmioClose(file, 0);
	return true;
}

void Sound::Play(bool loop)
{
	m_soundBuffer->SetCurrentPosition(0);

	if (loop)
		m_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_soundBuffer->Play(0, 0, 0);
}

void Sound::Stop(bool reset)
{
	m_soundBuffer->Stop();
	
	if (reset)	m_soundBuffer->SetCurrentPosition(0);
}

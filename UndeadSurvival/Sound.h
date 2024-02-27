#pragma once
#include "ResourceBase.h"
class Sound : public ResourceBase
{
public:
	Sound();
	virtual ~Sound();

	bool LoadWave(fs::path fullpath);
	void Play(bool loop = false);
	void Stop(bool reset = false);

private:
	virtual void Load(const wstring& path) {}
	virtual void Save(const wstring& path) {}

	LPDIRECTSOUNDBUFFER m_pBuffer{nullptr};
	DSBUFFERDESC m_dsbd{};
};


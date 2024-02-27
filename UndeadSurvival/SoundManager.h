#pragma once
class SoundManager
{
	CREATE_SINGLETONS(SoundManager);

public:
	~SoundManager();

	void Init(HWND hwnd);
	void Play(const wstring& name, bool loop = false);
	LPDIRECTSOUND GetDirectSound() { return m_pDirectSound; }

private:
	LPDIRECTSOUND m_pDirectSound{nullptr}; // ���� ī��
};


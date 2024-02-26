#pragma once
class GameModule
{
public:
	GameModule();
	~GameModule();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND m_hwnd{};
	HDC m_hdc{};

private:
	// Double Buffering
	RECT m_rect{};
	HDC m_backBufferDC{};
	HBITMAP m_backBufferBitmap{};
};


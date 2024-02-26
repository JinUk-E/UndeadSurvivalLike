#include "pch.h"
#include "GameModule.h"

GameModule::GameModule(){}
GameModule::~GameModule()
{
	/*GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();*/

	_CrtDumpMemoryLeaks();
}

void GameModule::Init(HWND hwnd)
{
	m_hwnd = hwnd;
	m_hdc = GetDC(m_hwnd);

	GetClientRect(m_hwnd, &m_rect);

	m_backBufferDC = CreateCompatibleDC(m_hdc); // hdc와 호환되는 메모리 dc 생성
	m_backBufferBitmap = CreateCompatibleBitmap(m_hdc, m_rect.right, m_rect.bottom); // hdc에 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)SelectObject(m_backBufferDC, m_backBufferBitmap); // 비트맵을 dc에 연결
	DeleteObject(prev);

}


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

	m_backBufferDC = CreateCompatibleDC(m_hdc); // hdc�� ȣȯ�Ǵ� �޸� dc ����
	m_backBufferBitmap = CreateCompatibleBitmap(m_hdc, m_rect.right, m_rect.bottom); // hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)SelectObject(m_backBufferDC, m_backBufferBitmap); // ��Ʈ���� dc�� ����
	DeleteObject(prev);

}


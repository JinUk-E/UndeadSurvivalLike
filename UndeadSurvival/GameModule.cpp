#include "pch.h"
#include "GameModule.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

GameModule::GameModule(){}
GameModule::~GameModule()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

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

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, fs::path(L""));
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SoundManager)->Init(hwnd);

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::Menu);
}

void GameModule::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void GameModule::Render()
{
	GET_SINGLE(SceneManager)->Render(m_backBufferDC);

	uint32 fps = GET_SINGLE(TimeManager)->GetFPS();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(m_backBufferDC, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(m_backBufferDC, 550, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering
	BitBlt(m_hdc, 0, 0, m_rect.right, m_rect.bottom, m_backBufferDC, 0, 0, SRCCOPY); // ��Ʈ �� ��� ����
	PatBlt(m_backBufferDC, 0, 0, m_rect.right, m_rect.bottom, WHITENESS); // ����۸� ������� ĥ��)
}


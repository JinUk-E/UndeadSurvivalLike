#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	m_hwnd = hwnd;
	m_KeyState.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT]{};
	if (!GetKeyboardState(asciiKeys)) return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		KeyState& state = m_KeyState[key];

		// 키가 눌렸는지 확인
		if (asciiKeys[key] & 0x80)
		{			
			// 이전 프레임에 키를 누르고 있는 상태라면
			if (state == KeyState::Down || state == KeyState::Press)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			// 이전 프레임에 키를 누르고 있었다면
			if (state == KeyState::Down || state == KeyState::Press)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	// 마우스 위치 업데이트
	GetCursorPos(&m_MousePos);
	ScreenToClient(m_hwnd, &m_MousePos);
}
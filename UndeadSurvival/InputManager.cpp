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

		// Ű�� ���ȴ��� Ȯ��
		if (asciiKeys[key] & 0x80)
		{			
			// ���� �����ӿ� Ű�� ������ �ִ� ���¶��
			if (state == KeyState::Down || state == KeyState::Press)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			// ���� �����ӿ� Ű�� ������ �־��ٸ�
			if (state == KeyState::Down || state == KeyState::Press)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	// ���콺 ��ġ ������Ʈ
	GetCursorPos(&m_MousePos);
	ScreenToClient(m_hwnd, &m_MousePos);
}
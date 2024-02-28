#pragma once


class InputManager
{
	CREATE_SINGLETONS(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

	// key down check
	bool IsKeyDown(KeyType keyType) { return GetState(keyType) == KeyState::Press; }
	
	// key press check
	bool IsKeyPress(KeyType keyType) { return GetState(keyType) == KeyState::Down; }

	// key up check
	bool IsKeyUp(KeyType keyType) { return GetState(keyType) == KeyState::Up; }

	// mouse position
	POINT GetMousePos() { return m_MousePos; }


private:
	KeyState GetState(KeyType keyType) { return m_KeyState[static_cast<int32>(keyType)]; }

private:
	HWND m_hwnd{};
	vector<KeyState> m_KeyState{};
	POINT m_MousePos{};
};


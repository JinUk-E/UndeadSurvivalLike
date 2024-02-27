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
	POINT GetMousePos() { return mMousePos; }


private:
	KeyState GetState(KeyType keyType) { return mKeyState[static_cast<int32>(keyType)]; }

private:
	HWND mHwnd{};
	vector<KeyState> mKeyState{};
	POINT mMousePos{};
};


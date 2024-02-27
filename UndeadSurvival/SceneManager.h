#pragma once

class Scene;

class SceneManager
{
	CREATE_SINGLETONS(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Clear();

	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() { return currentScene; }

	// Camera
	Position GetCameraPos() { return m_cameraPos; }
	void SetCameraPos(Position pos) { m_cameraPos = pos; }

private:
	Scene* currentScene{};
	SceneType m_SceneType{ SceneType::Menu };
	Position m_cameraPos{400,300};

};


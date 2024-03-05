#include "pch.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "InGameScene.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if(currentScene)
		currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if(currentScene)
		currentScene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(currentScene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if(m_SceneType == sceneType) return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
		case SceneType::Menu:
			newScene = new MenuScene();
			break;
		case SceneType::Game:
			newScene = new InGameScene();
			break;
	}
	Clear();

	currentScene = newScene;
	m_SceneType = sceneType;

	newScene->Init();
}
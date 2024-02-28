#pragma once
#include "Scene.h"

class Actor;
class GameObject;
class UI;

class LoadingScene : public Scene
{
	using Super = Scene;
public:
	LoadingScene();
	virtual ~LoadingScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	bool CanGo(PosInt cellPos);
	Position ConvertPos(PosInt cellPos);

	class TilemapActor* _tilemapActor = nullptr;
};


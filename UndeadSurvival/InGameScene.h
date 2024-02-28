#pragma once
#include "Scene.h"

class Actor;
class GameObject;
class UI;

class InGameScene : public Scene
{
	using Super = Scene;
public:
	InGameScene();
	virtual ~InGameScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	bool CanGo(PosInt cellPos);
	Position ConvertPos(PosInt cellPos);

	class TilemapActor* _tilemapActor = nullptr;
};


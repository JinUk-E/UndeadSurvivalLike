#pragma once
#include "Scene.h"

class Actor;
class GameObject;
class UI;

class MenuScene : public Scene
{
	using Super = Scene;

	public:
		MenuScene();
		virtual ~MenuScene() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		bool CanGo(PosInt cellPos);
		Position ConvertPos(PosInt cellPos);

		class TilemapActor* _tilemapActor = nullptr;
};


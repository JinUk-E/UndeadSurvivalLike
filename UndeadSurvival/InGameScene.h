#pragma once
#include "Scene.h"

class Actor;
class GameObject;
class UI;
class Player;

class InGameScene : public Scene
{
	using Super = Scene;
private:
	Player* m_player{ nullptr };
public:
	InGameScene();
	virtual ~InGameScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	bool CanGo(PosInt cellPos);
	Position ConvertPos(PosInt cellPos);
	PosInt GetPlayerPos() const;
	class TilemapActor* _tilemapActor = nullptr;
};


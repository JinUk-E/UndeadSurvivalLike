#include "pch.h"
#include "MenuScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Button.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "SoundManager.h"
#include "Sound.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init()
{


	Super::Init();
}

void MenuScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
}

void MenuScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

bool MenuScene::CanGo(PosInt cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return false;

	Tile* tile = tm->GetTileAt(cellPos);
	if (tile == nullptr)
		return false;

	return tile->value != 1;
}

Position MenuScene::ConvertPos(PosInt cellPos)
{
	Position ret{};

	if(_tilemapActor == nullptr)
		return ret;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr) return ret;

	int32 size = tm->GetTileSize();
	Position pos = _tilemapActor->GetPos();

	ret.X = pos.X + cellPos.X * size + (size * 0.5f);
	ret.Y = pos.Y + cellPos.Y * size + (size * 0.5f);

	return ret;
}
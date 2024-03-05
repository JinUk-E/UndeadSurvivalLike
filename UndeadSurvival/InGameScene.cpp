#include "pch.h"
#include "InGameScene.h"
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

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Init()
{
	// 초기 리소스 불러오기



	Super::Init();
}

void InGameScene::Update()
{
	Super::Update();
}

void InGameScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

bool InGameScene::CanGo(PosInt pos)
{
	if(!_tilemapActor) return false;

	Tilemap* tilemap = _tilemapActor->GetTilemap();
	
	if(!tilemap) return false;

	Tile* tile = tilemap->GetTileAt(pos);

	if(!tile) return false;

	return tile->value != 1;
}

Position InGameScene::ConvertPos(PosInt cellPos)
{
	Position ret{};
	if(!_tilemapActor) return ret;
	Tilemap* tilemap = _tilemapActor->GetTilemap();
	if(!tilemap) return ret;

	int32 size = tilemap->GetTileSize();
	Position pos = _tilemapActor->GetPos();

	ret.X = pos.X + cellPos.X * size + (size * .5f);
	ret.Y = pos.Y + cellPos.Y * size + (size * .5f);

	return ret;
}
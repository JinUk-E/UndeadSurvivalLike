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
#include "Enemy.h"
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
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	// IDLE
	CreateCharacterFlipbook(L"PlayerUp", L"FB_IdleUp", L"FB_MoveUp", { 200, 200 }, 0, 9, 0, 0.5f);
	CreateCharacterFlipbook(L"PlayerDown", L"FB_IdleDown", L"FB_MoveDown", { 200, 200 }, 0, 9, 0, 0.5f);
	CreateCharacterFlipbook(L"PlayerLeft", L"FB_IdleLeft", L"FB_MoveLeft", { 200, 200 }, 0, 9, 0, 0.5f);
	CreateCharacterFlipbook(L"PlayerRight", L"FB_IdleRight", L"FB_MoveRight", { 200, 200 }, 0, 9, 0, 0.5f);	
	// MOVE
	CreateCharacterFlipbook(L"PlayerUp", L"FB_MoveUp", L"FB_MoveUp", { 200, 200 }, 0, 9, 1, 0.5f);
	CreateCharacterFlipbook(L"PlayerDown", L"FB_MoveDown", L"FB_MoveDown", { 200, 200 }, 0, 9, 1, 0.5f);
	CreateCharacterFlipbook(L"PlayerLeft", L"FB_MoveLeft", L"FB_MoveLeft", { 200, 200 }, 0, 9, 1, 0.5f);
	CreateCharacterFlipbook(L"PlayerRight", L"FB_MoveRight", L"FB_MoveRight", { 200, 200 }, 0, 9, 1, 0.5f);
	// SKILL
	CreateCharacterFlipbook(L"PlayerUp", L"FB_SkillUp", L"FB_MoveUp", { 200, 200 }, 0, 7, 3, 0.5f);
	CreateCharacterFlipbook(L"PlayerDown", L"FB_SkillDown", L"FB_MoveDown", { 200, 200 }, 0, 7, 3, 0.5f);
	CreateCharacterFlipbook(L"PlayerLeft", L"FB_SkillLeft", L"FB_MoveLeft", { 200, 200 }, 0, 7, 3, 0.5f);
	CreateCharacterFlipbook(L"PlayerRight", L"FB_SkillRight", L"FB_MoveRight", {200, 200}, 0, 7, 3, 0.5f);

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayerType(LAYER_BACKGROUND);
		const PosInt size = sprite->GetSize();
		background->SetPos(Position(size.X *.5f, size.Y * .5f));

		AddActor(background);
	}

	{
		Player* player = new Player();
		m_player = player;
		AddActor(player);
	}
	
	{
		TilemapActor* actor = new TilemapActor();
		AddActor(actor);

		_tilemapActor = actor;
		{
			auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			tm->SetMapSize({ 63, 43 });
			tm->SetTileSize(48);

			GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01_FINAL.txt");

			_tilemapActor->SetTilemap(tm);
			_tilemapActor->SetShowDebug(false);
		}
	}

	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	{
		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		sound->Play(true);
	}

	GET_SINGLE(ResourceManager)->LoadSound(L"Attack", L"Sound\\Sword.wav");


	Super::Init();
}

void InGameScene::Update()
{
	Super::Update();
	// Enemy를 플레이어 주변에 소환
	//if (m_player)
	//{
	//	PosInt playerPos = m_player->GetCellPos();
	//	PosInt enemyPos = playerPos;
	//	enemyPos.X += 5;
	//	enemyPos.Y += 5;
	//	Enemy* enemy = new Enemy();
	//	enemy->SetCellPos(enemyPos);
	//	AddActor(enemy);
	//}
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

PosInt InGameScene::GetPlayerPos() const
{
	if(!m_player) return PosInt{0 , 0};

	return m_player->GetCellPos();
}

void InGameScene::CreateCharacterFlipbook(const wstring& dir,const wstring& fbName,const wstring& settingName,
	PosInt size, int32 startFrame, int32 endFrame, int32 lineCount, float duration)
{
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(dir);
	Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(fbName);
	fb->SetInfo({ texture, fbName, size, startFrame, endFrame, lineCount, duration });
}
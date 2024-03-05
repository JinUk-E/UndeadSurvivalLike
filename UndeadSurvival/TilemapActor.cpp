#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "InputManager.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Actor::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if(!mTilemap || !mShowDebug)
		return;

	// Draw tilemap
	const PosInt mapSize = mTilemap->GetMapSize();
	const int32 tileSize = mTilemap->GetTileSize();

	vector<vector<Tile>>& tiles = mTilemap->GetTiles();

	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");
	PosInt size = spriteO->GetSize();
	Position cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// 컬링 : 보여야 할 애들만 보여주기
	int32 leftX = ((int32)cameraPos.X - GwinSizeX * 0.5f);
	int32 leftY = ((int32)cameraPos.Y - GwinSizeY * 0.5f);
	int32 rightX = ((int32)cameraPos.X + GwinSizeX * 0.5f);
	int32 rightY = ((int32)cameraPos.Y + GwinSizeY * 0.5f);

	int32 startX = (leftX - _pos.X) / TILE_SIZEX;
	int32 startY = (leftY - _pos.Y) / TILE_SIZEY;
	int32 endX = (rightX - _pos.X) / TILE_SIZEX;
	int32 endY = (rightY - _pos.Y) / TILE_SIZEY;


	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.X)
				continue;
			if (y < 0 || y >= mapSize.Y)
				continue;
			// 왼쪽 상단 모서리를 기준으로 맞추자
			switch (tiles[y][x].value)
			{
				case 0:
				{
					::TransparentBlt(hdc,
						_pos.X + x * TILE_SIZEX - ((int32)cameraPos.X - GwinSizeX * .5f),
						_pos.Y + y * TILE_SIZEY - ((int32)cameraPos.Y - GwinSizeY * .5f),
						TILE_SIZEX,
						TILE_SIZEY,
						spriteO->GetDC(),
						spriteO->GetPos().X,
						spriteO->GetPos().Y,
						TILE_SIZEX,
						TILE_SIZEY,
						spriteO->GetTransparent());
				}
				break;
				case 1:
					::TransparentBlt(hdc,
						_pos.X + x * TILE_SIZEX - ((int32)cameraPos.X - GwinSizeX * .5f),
						_pos.Y + y * TILE_SIZEY - ((int32)cameraPos.Y - GwinSizeY * .5f),
						TILE_SIZEX,
						TILE_SIZEY,
						spriteX->GetDC(),
						spriteX->GetPos().X,
						spriteX->GetPos().Y,
						TILE_SIZEX,
						TILE_SIZEY,
						spriteX->GetTransparent());
					break;
				}
		}
	}
}

void TilemapActor::TickPicking()
{
	if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::LeftMouse))
	{
		Position cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		int32 screenX = cameraPos.X - GwinSizeX * .5f;
		int32 screenY = cameraPos.Y - GwinSizeY * .5f;

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = mTilemap->GetTileAt({ x, y });
		
		if (tile) tile->value = 1;
	}
}
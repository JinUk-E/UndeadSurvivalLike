#pragma once
#include "Actor.h"

class Tilemap;

class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void TickPicking();

	void SetTilemap(Tilemap* tilemap) { mTilemap = tilemap; }
	Tilemap* GetTilemap() { return mTilemap; }

	void SetShowDebug(bool show) { mShowDebug = show; }

protected:
	Tilemap* mTilemap{nullptr};
	bool mShowDebug{ false };
};


#pragma once
#include "ResourceBase.h"

struct Tile
{
	int32 value{ 0 };
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap();

	virtual void Load(const std::wstring& path) override;
	virtual void Save(const std::wstring& path) override;

	PosInt GetMapSize() { return _mapSize; }
	int32 GetTileSize() { return _tileSize; }
	Tile* GetTileAt(int32 x, int32 y);
	Tile* GetTileAt(PosInt pos);
	vector<vector<Tile>>& GetTiles() { return _tiles; }

	void SetMapSize(PosInt size);
	void SetTileSize(int32 size);

private:
	PosInt _mapSize{};
	int32 _tileSize{};
	vector<vector<Tile>> _tiles;
};


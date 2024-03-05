#include "pch.h"
#include "Tilemap.h"
#include <iostream>
#include <fstream>

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::Load(const wstring& path)
{
	// C++ 스타일
	{
		wifstream ifs;

		ifs.open(path);

		ifs >> _mapSize.X >> _mapSize.Y;

		SetMapSize(_mapSize);

		for (int32 y = 0; y < _mapSize.Y; y++)
		{
			wstring line;
			ifs >> line;

			for (int32 x = 0; x < _mapSize.X; x++)
			{
				_tiles[y][x].value = line[x] - L'0';
			}
		}

		ifs.close();
	}

}

void Tilemap::Save(const wstring& path)
{
	// C++ 스타일
	{
		wofstream ofs;

		ofs.open(path);

		ofs << _mapSize.X << endl;
		ofs << _mapSize.Y << endl;

		for (int32 y = 0; y < _mapSize.Y; y++)
		{
			for (int32 x = 0; x < _mapSize.X; x++)
			{
				ofs << _tiles[y][x].value;
			}

			ofs << endl;
		}

		ofs.close();
	}
}

Tile* Tilemap::GetTileAt(PosInt pos)
{
	if (pos.X < 0 || pos.X >= _mapSize.X || pos.Y < 0 || pos.Y >= _mapSize.Y)
		return nullptr;

	return &_tiles[pos.Y][pos.X];
}

Tile* Tilemap::GetTileAt(int32 x, int32 y)
{
	if (x < 0 || x >= _mapSize.X || y < 0 || y >= _mapSize.Y)
		return nullptr;

	return &_tiles[y][x];
}

void Tilemap::SetMapSize(PosInt size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.Y, vector<Tile>(size.X));

	for (int32 y = 0; y < size.Y; y++)
	{
		for (int32 x = 0; x < size.X; x++)
		{
			_tiles[y][x] = Tile{ 0 };
		}
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}

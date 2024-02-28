#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"
#include "Sound.h"

ResourceManager::~ResourceManager() { Clear(); }

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	m_hwnd = hwnd;
	m_resourcePath = resourcePath;
}

void ResourceManager::Clear()
{
	for (auto& [name, texture] : m_textures)
		SAFE_DELETE(texture);
	m_textures.clear();

	for (auto& [name, sprite] : m_sprites)
		SAFE_DELETE(sprite);
	m_sprites.clear();

	for (auto& [name, flipbook] : m_flipbooks)
		SAFE_DELETE(flipbook);
	m_flipbooks.clear();

	for (auto& [name, tilemap] : m_tilemaps)
		SAFE_DELETE(tilemap);
	m_tilemaps.clear();

	for (auto& [name, sound] : m_sounds)
		SAFE_DELETE(sound);
	m_sounds.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& name, const wstring& path, uint32 transparent)
{
	if(m_textures.find(name) != m_textures.end())
		return m_textures[name];

	fs::path fullPath = m_resourcePath / path;
	
	Texture* texture = new Texture();
	texture->LoadBmp(m_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	m_textures[name] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& name, Texture* texture, int32 x, int32 y, int32 w, int32 h)
{
	if(m_sprites.find(name) != m_sprites.end())
		return m_sprites[name];

	if (w == 0 || h == 0)
	{
		w = texture->GetSize().X;
		h = texture->GetSize().Y;
	}

	Sprite* sprite = new Sprite(texture, x, y, w, h);
	m_sprites[name] = sprite;

	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& name)
{
	if(m_flipbooks.find(name) != m_flipbooks.end())
		return m_flipbooks[name];

	Flipbook* flipbook = new Flipbook();
	m_flipbooks[name] = flipbook;

	return flipbook;
}

Tilemap* ResourceManager::CreateTilemap(const wstring& key)
{
	if(m_tilemaps.find(key) != m_tilemaps.end())
		return m_tilemaps[key];

	Tilemap* tilemap = new Tilemap();
	m_tilemaps[key] = tilemap;

	return tilemap;
}

void ResourceManager::SaveTilemap(const wstring& name, const wstring& path)
{
	if(m_tilemaps.find(name) == m_tilemaps.end())
		return;

	fs::path fullPath = m_resourcePath / path;
	m_tilemaps[name]->Save(fullPath);
}

Tilemap* ResourceManager::LoadTilemap(const wstring& name, const wstring& path)
{
	Tilemap* tilemap = nullptr;

	if(m_tilemaps.find(name) == m_tilemaps.end())
		m_tilemaps[name] = new Tilemap();
	
	tilemap = m_tilemaps[name];

	fs::path fullPath = m_resourcePath / path;
	tilemap->Load(fullPath);

	return tilemap;
}

Sound* ResourceManager::LoadSound(const wstring& name, const wstring& path)
{
	if(m_sounds.find(name) != m_sounds.end())
		return m_sounds[name];

	fs::path fullPath = m_resourcePath / path;

	Sound* sound = new Sound();
	sound->LoadWave(fullPath);
	m_sounds[name] = sound;

	return sound;
}




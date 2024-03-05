#pragma once

class ResourceBase;
class LineMesh;
class Texture;
class Sprite;
class Flipbook;
class Tilemap;
class Sound;

class ResourceManager
{
	CREATE_SINGLETONS(ResourceManager);
public:
	~ResourceManager();

	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	const fs::path& GetResourcePath() const { return m_resourcePath; }

	Texture* GetTexture(const wstring& name) { return m_textures[name]; }
	Texture* LoadTexture(const wstring& name, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const wstring& name) { return m_sprites[name]; }
	Sprite* CreateSprite(const wstring& name, Texture* texture, int32 x = 0, int32 y = 0, int32 w = 0, int32 h = 0);

	Flipbook* GetFlipbook(const wstring& name) { return m_flipbooks[name]; }
	Flipbook* CreateFlipbook(const wstring& name);

	Tilemap* GetTilemap(const wstring& key) { return m_tilemaps[key]; }
	Tilemap* CreateTilemap(const wstring& key);
	void SaveTilemap(const wstring& name, const wstring& path);
	Tilemap* LoadTilemap(const wstring& name, const wstring& path);

	Sound* GetSound(const wstring& name) { return m_sounds[name]; }
	Sound* LoadSound(const wstring& name, const wstring& path);

	const LineMesh* GetLineMesh(wstring key);
private:
	HWND m_hwnd{};
	fs::path m_resourcePath{};

	unordered_map<wstring, Texture*> m_textures{};
	unordered_map<wstring, Sprite*> m_sprites{};
	unordered_map<wstring, Flipbook*> m_flipbooks{};
	unordered_map<wstring, Tilemap*> m_tilemaps{};
	unordered_map<wstring, Sound*> m_sounds{};
	unordered_map<wstring, LineMesh*> _lineMeshes;
};


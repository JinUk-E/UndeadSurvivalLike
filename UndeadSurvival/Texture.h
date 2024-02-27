#pragma once
#include "ResourceBase.h"
class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();
	
	Texture* LoadBmp(HWND hwnd, const wstring& path);
	HDC GetDc();

	void SetSize(PosInt size){ m_size = size; }
	PosInt GetSize(){ return m_size; }	

	void SetTransparent(uint32 transparent){ m_transparent = transparent; }
	uint32 GetTransparent(){ return m_transparent; }

private:
	HDC m_hdc{};
	HBITMAP m_hBitmap{};
	PosInt m_size{};
	uint32 m_transparent{RGB(255,0,255)};
};


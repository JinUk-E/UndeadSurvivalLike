#include "pch.h"
#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

Texture* Texture::LoadBmp(HWND hwnd, const wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	m_hdc = ::CreateCompatibleDC(hdc);

	m_hBitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (m_hBitmap == NULL)
	{
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
	}

	HBITMAP prev = (HBITMAP)::SelectObject(m_hdc, m_hBitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(m_hBitmap, sizeof(BITMAP), &bit);
	m_size.X = bit.bmWidth;
	m_size.Y = bit.bmHeight;

	return this;
}

HDC Texture::GetDc()
{
	return m_hdc;
}

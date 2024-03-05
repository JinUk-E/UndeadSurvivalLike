#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Position pos, const wstring& str)
{TextOut(hdc, static_cast<int32>(pos.X), static_cast<int32>(pos.Y), str.c_str(), static_cast<int32>(str.size()));}

void Utils::DrawRect(HDC hdc, Position pos, int32 width, int32 height)
{
	int32 halfWidth = width*.5;
	int32 halfHeight = height*.5;
	Rectangle(hdc, static_cast<int32>(pos.X - halfWidth), static_cast<int32>(pos.Y - halfHeight), static_cast<int32>(pos.X + halfWidth), static_cast<int32>(pos.Y + halfHeight));
}

void Utils::DrawCircle(HDC hdc, Position pos, int32 radius)
{
	Ellipse(hdc, static_cast<int32>(pos.X - radius), static_cast<int32>(pos.Y - radius), static_cast<int32>(pos.X + radius), static_cast<int32>(pos.Y + radius));
}

void Utils::DrawLine(HDC hdc, Position start, Position end)
{
	MoveToEx(hdc, static_cast<int32>(start.X), static_cast<int32>(start.Y), nullptr);
	LineTo(hdc, static_cast<int32>(end.X), static_cast<int32>(end.Y));
}

void Utils::DrawLineColored(HDC hdc, Position start, Position end, COLORREF color)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = static_cast<HPEN>(SelectObject(hdc, hPen));

	MoveToEx(hdc, static_cast<int32>(start.X), static_cast<int32>(start.Y), nullptr);
	LineTo(hdc, static_cast<int32>(end.X), static_cast<int32>(end.Y));

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

void Utils::ReadBmp(const wstring& path)
{
	FILE* filepath{};
	if (_wfopen_s(&filepath, path.c_str(), L"rb") != 0)
	{
		MessageBox(nullptr, L"File Open Error", L"Error", MB_OK);
		return;
	}
	BITMAPFILEHEADER fileHeader{};
	fread_s(&fileHeader, sizeof(fileHeader), sizeof(fileHeader), 1, filepath);

	BITMAPINFOHEADER infoHeader{};	
	fread_s(&infoHeader, sizeof(infoHeader), sizeof(infoHeader), 1, filepath);

	int32 imgSize = infoHeader.biWidth * infoHeader.biHeight * 4;
	char* buffer = static_cast<char*>(malloc(imgSize));
	if (buffer != 0) fread_s(buffer, imgSize, imgSize, 1, filepath);
}


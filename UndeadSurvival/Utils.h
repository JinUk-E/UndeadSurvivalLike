#pragma once
#include <windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Position pos, const wstring& str);

	static void DrawRect(HDC hdc, Position pos, int32 width, int32 height);

	static void DrawCircle(HDC hdc, Position pos, int32 radius);

	static void DrawLine(HDC hdc, Position start, Position end);

	static void DrawLineColored(HDC hdc, Position start, Position end, COLORREF color);

	static void ReadBmp(const wstring& path);
};


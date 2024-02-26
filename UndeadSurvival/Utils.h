#pragma once
#include <windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Postion pos, const wstring& str);

	static void DrawRect(HDC hdc, Postion pos, int32 width, int32 height);

	static void DrawCircle(HDC hdc, Postion pos, int32 radius);

	static void DrawLine(HDC hdc, Postion start, Postion end);

	static void DrawLineColored(HDC hdc, Postion start, Postion end, COLORREF color);

	static void ReadBmp(const wstring& path);
};


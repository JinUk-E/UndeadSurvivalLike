#pragma once
#include "ResourceBase.h"

class LineMesh : public ResourceBase
{
public:
	void Save(wstring path);
	void Load(wstring path);
	void Render(HDC hdc, Position pos, float ratioX = 1.0f, float ratioY = 1.0f) const;
	vector<pair<POINT,POINT>>& GetLines() { return m_lines; }

protected:
	vector<pair<POINT, POINT>> m_lines;
	int32 m_width{0};
	int32 m_height{0};
};


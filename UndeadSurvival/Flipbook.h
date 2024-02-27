#pragma once
#include "ResourceBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture{ nullptr };
	wstring name{};
	PosInt size{};
	int32 startFrame{ 0 };
	int32 endFrame{ 0 };
	int32 lineCount{ 0 };
	float duration{ 1.0f };
	bool isLoop{ true };
};

class Flipbook :  public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook();

	void SetInfo(const FlipbookInfo& info) { m_Info = info; }
	const FlipbookInfo& GetInfo() const { return m_Info; }

private:
	FlipbookInfo m_Info;
};


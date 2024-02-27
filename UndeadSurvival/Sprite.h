#pragma once
#include "ResourceBase.h"

class Texture;

class Sprite : public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 width, int32 height);
	virtual ~Sprite();

	HDC GetDC();
	int32 GetTransparent();
	PosInt GetPos() { return PosInt{ _x,_y }; }
	PosInt GetSize(){ return PosInt{ _width,_height }; }

private:
	Texture* _texture{nullptr};
	int32 _x{ 0 };
	int32 _y{ 0 };
	int32 _width{ 0 };
	int32 _height{ 0 };
};


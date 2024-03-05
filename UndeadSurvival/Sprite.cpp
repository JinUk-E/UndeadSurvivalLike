#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
	: _texture(texture), _x(x), _y(y), _width(cx), _height(cy)
{

}

Sprite::~Sprite()
{

}

HDC Sprite::GetDC()
{
	return _texture->GetDc();
}

int32 Sprite::GetTransparent()
{
	return _texture->GetTransparent();
}

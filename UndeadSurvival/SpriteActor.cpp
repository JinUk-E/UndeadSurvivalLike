#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Actor::BeginPlay();
}

void SpriteActor::Tick()
{
	Actor::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if(!m_Sprite) return;

	PosInt size = m_Sprite->GetSize();
	Position cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	int32 x = (int32)(_pos.X - size.X * .5f - (int32)cameraPos.X - GwinSizeX * .5f);
	int32 y = (int32)(_pos.Y - size.Y * .5f - (int32)cameraPos.Y - GwinSizeY * .5f);

	::BitBlt(hdc, x, y, size.X, size.Y, m_Sprite->GetDC(), m_Sprite->GetPos().X, m_Sprite->GetPos().Y, SRCCOPY);
}

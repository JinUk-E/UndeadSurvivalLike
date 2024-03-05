#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Texture.h"
#include "Sprite.h"
#include "TimeManager.h"
#include "SceneManager.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	if (!_flipbook) return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if(!info.isLoop && _idx == info.endFrame) return;

	_sumTime += GET_SINGLE(TimeManager)->GetDeltaTime();

	int32 frameCount = info.endFrame - info.startFrame + 1;
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_flipbook) return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	Position cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	::TransparentBlt(hdc,
		(int32)_pos.X - info.size.Y * .5f - ((int32)cameraPos.X - GwinSizeX * .5f),
		(int32)_pos.Y - info.size.Y * .5f - ((int32)cameraPos.Y - GwinSizeY * .5f),
		info.size.X,
		info.size.Y,
		info.texture->GetDc(),
		(info.startFrame + _idx) * info.size.X,
		info.lineCount * info.size.Y,
		info.size.X,
		info.size.Y,
		info.texture->GetTransparent());
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	if(flipbook && _flipbook == flipbook) return;

	_flipbook = flipbook;
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}
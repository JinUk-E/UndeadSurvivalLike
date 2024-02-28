#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(& _frequency));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>( & _prevCount));
}

void TimeManager::Update()
{
	uint64 currentCount;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(& currentCount));

	_deltaTime = static_cast<float>(currentCount - _prevCount) / _frequency;
	_prevCount = currentCount;

	_fpsTime += _deltaTime;
	_frameCount++;

	if (_fpsTime >= 1.0f)
	{
		_fps = static_cast<uint32>(_frameCount / _fpsTime);
		_frameCount = 0;
		_fpsTime = 0.0f;
	}
}
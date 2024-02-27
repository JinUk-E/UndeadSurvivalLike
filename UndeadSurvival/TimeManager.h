#pragma once
class TimeManager
{
	CREATE_SINGLETONS(TimeManager);

public:
	void Init();
	void Update();

	uint32 GetFPS() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64 _frequency{ 0 };
	uint64 _prevCount{ 0 };
	uint32 _frameCount{ 0 };
	uint32 _fps{ 0 };
	float _deltaTime{ 0.0f };
	float _fpsTime{ 0.0f };
};


#pragma once
#include "FlipbookActor.h"

class Flipbook;
class Collider;
class BoxColliider;

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickSkill();

	void SetState(PlayerState state);
	void SetDirection(DIRECTION direction);

	void UpdateAnimation();

	bool HasReachedDestination();
	bool CanGo(PosInt cellPos);
	void SetCellPos(PosInt cellPos, bool teleport = false);
	void InputMachine(DIRECTION dir, PosInt deltaXY);

	Flipbook* m_idleFlipbook[4]{}; 
	Flipbook* m_moveFlipbook[4]{}; 
	Flipbook* m_skillFlipbook[4]{};

	PosInt m_cellPos{};
	Position m_speed{};
	DIRECTION m_direction{ DIRECTION::DIRECTION_DOWN};
	PlayerState m_state{ PlayerState::Idle};
	bool _keyPressed{ false };
};


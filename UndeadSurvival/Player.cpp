#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "InGameScene.h"
#include <iostream>

Player::Player()
{
	m_idleFlipbook[DIRECTION_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleUp");
	m_idleFlipbook[DIRECTION_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleDown");
	m_idleFlipbook[DIRECTION_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleLeft");
	m_idleFlipbook[DIRECTION_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleRight");

	m_moveFlipbook[DIRECTION_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveUp");
	m_moveFlipbook[DIRECTION_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveDown");
	m_moveFlipbook[DIRECTION_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft");
	m_moveFlipbook[DIRECTION_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight");

	m_skillFlipbook[DIRECTION_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackUp");
	m_skillFlipbook[DIRECTION_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackDown");
	m_skillFlipbook[DIRECTION_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackLeft");
	m_skillFlipbook[DIRECTION_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackRight");

	CameraComponent* camera = new CameraComponent;
	ADDComponent(camera);
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(PlayerState::Move);
	SetState(PlayerState::Idle);

	SetCellPos({ 5, 5 }, true);
}

void Player::Tick()
{
	Super::Tick();

	switch (m_state)
	{
	case PlayerState::Idle:
		TickIdle();
		break;
	case PlayerState::Move:
		TickMove();
		break;
	case PlayerState::Skill:
		TickSkill();
		break;
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_keyPressed = true;
	PosInt deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::W)) InputMachine(DIRECTION_UP, deltaXY[DIRECTION_UP]);
	else if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::S)) InputMachine(DIRECTION_DOWN, deltaXY[DIRECTION_DOWN]);
	else if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::D)) InputMachine(DIRECTION_RIGHT, deltaXY[DIRECTION_RIGHT]);
	else if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::A)) InputMachine(DIRECTION_LEFT, deltaXY[DIRECTION_LEFT]);
	else
	{
		_keyPressed = false;
		// µð¹ö±ë Ãâ·Â
		std::cout << "Idle" << std::endl;
		if (m_state == PlayerState::Idle) UpdateAnimation();
	}
}

void Player::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Position dir = _destPos - _pos;

	if (dir.Length() < 10.f)
	{
		SetState(PlayerState::Idle);
		_pos = _destPos;
	}
	else
	{
	/*_pos.X = (m_direction == DIRECTION_RIGHT) ? _pos.X - (200 * deltaTime) : 
		(m_direction == DIRECTION_LEFT) ? _pos.X + (200 * deltaTime) : _destPos.X;

	_pos.Y = (m_direction == DIRECTION_DOWN) ? _pos.Y + (200 * deltaTime) :
		(m_direction == DIRECTION_UP) ? _pos.Y - (200 * deltaTime) : _destPos.Y;*/
		switch (m_direction)
		{
		case DIRECTION_UP:
			_pos.Y -= 200 * deltaTime;
			break;
		case DIRECTION_DOWN:
			_pos.Y += 200 * deltaTime;
			break;
		case DIRECTION_LEFT:
			_pos.X -= 200 * deltaTime;
			break;
		case DIRECTION_RIGHT:
			_pos.X += 200 * deltaTime;
			break;
		}
	}
}

void Player::TickSkill()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// µð¹ö±ë Ãâ·Â
	std::cout << "Skill" << std::endl;
	if (m_state == PlayerState::Skill) UpdateAnimation();
}

void Player::SetState(PlayerState state)
{
	if(m_state == state) return;

	m_state = state;
	UpdateAnimation();
}

void Player::SetDirection(DIRECTION dir)
{
	m_direction = dir;
	UpdateAnimation();
}

void Player::UpdateAnimation()
{
	switch (m_state)
	{
		case PlayerState::Idle:
			SetFlipbook((_keyPressed) ? m_moveFlipbook[m_direction] : m_idleFlipbook[m_direction]);
			break;
		case PlayerState::Move:
			SetFlipbook(m_moveFlipbook[m_direction]);
			break;
		case PlayerState::Skill:
			SetFlipbook(m_skillFlipbook[m_direction]);
			break;
	}
}

bool Player::HasReachedDestination()
{
	Position dir = _destPos - _pos;
	return dir.Length() < 10.f;
}

bool Player::CanGo(PosInt cellPos)
{
	InGameScene* scene = dynamic_cast<InGameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	if (!scene) return false;

	return scene->CanGo(cellPos);
}

void Player::SetCellPos(PosInt cellPos, bool teleport)
{
	m_cellPos = cellPos;

	InGameScene* scene = dynamic_cast<InGameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	if (!scene) return;

	_destPos = scene->ConvertPos(m_cellPos);

	if(teleport) _pos = _destPos;
}


void Player::InputMachine(DIRECTION dir, PosInt deltaXY)
{
	SetDirection(dir);

	PosInt nextPos = m_cellPos + deltaXY;
	if (CanGo(nextPos))
	{
		SetCellPos(nextPos);
		SetState(PlayerState::Move);
	}
}


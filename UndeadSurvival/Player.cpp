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

Player::Player()
{
	m_idleFlipbook[DIRECTION_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerIdleUp");
	m_idleFlipbook[DIRECTION_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerIdleDown");
	m_idleFlipbook[DIRECTION_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerIdleLeft");
	m_idleFlipbook[DIRECTION_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerIdleRight");

	m_moveFlipbook[DIRECTION_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerMoveUp");
	m_moveFlipbook[DIRECTION_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerMoveDown");
	m_moveFlipbook[DIRECTION_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerMoveLeft");
	m_moveFlipbook[DIRECTION_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerMoveRight");

	m_skillFlipbook[DIRECTION_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerSkillUp");
	m_skillFlipbook[DIRECTION_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerSkillDown");
	m_skillFlipbook[DIRECTION_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerSkillLeft");
	m_skillFlipbook[DIRECTION_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"PlayerSkillRight");

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

	if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::D)) InputMachine(DIRECTION_LEFT);
	else if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::A)) InputMachine(DIRECTION_RIGHT);
	else if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::W)) InputMachine(DIRECTION_UP);
	else if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::S)) InputMachine(DIRECTION_DOWN);
	else
	{
		_keyPressed = false;
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
		return;
	}

	_pos.X = (m_direction == DIRECTION_RIGHT) ? _pos.X + (200 * deltaTime) : 
		(m_direction == DIRECTION_RIGHT) ? _pos.X - (200 * deltaTime) : _pos.X;

	_pos.Y = (m_direction == DIRECTION_DOWN) ? _pos.Y + (200 * deltaTime) :
		(m_direction == DIRECTION_UP) ? _pos.Y - (200 * deltaTime) : _pos.Y;
}

void Player::TickSkill()
{

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


void Player::InputMachine(DIRECTION dir)
{
	SetDirection(dir);

	PosInt nextPos = m_cellPos + deltaXY[dir];
	if (CanGo(nextPos))
	{
		SetCellPos(nextPos);
		SetState(PlayerState::Move);
	}
}


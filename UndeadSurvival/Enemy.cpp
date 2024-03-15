#include "pch.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "InGameScene.h"
#include "Player.h"

Enemy::Enemy()
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
}

Enemy::~Enemy(){}

void Enemy::BeginPlay()
{
	Super::BeginPlay();

	SetState(PlayerState::Move);
	SetState(PlayerState::Idle);

	//SetCellPos({ 5, 5 }, true);
}

void Enemy::Tick()
{
	Super::Tick();
	GetDirectionToPlayer();
	
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::TickIdle()
{
	UpdateAnimation();
}

void Enemy::TickMove()
{
	UpdateAnimation();
}

void Enemy::TickSkill()
{
	UpdateAnimation();
}

void Enemy::SetState(PlayerState state)
{
	m_state = state;
}

void Enemy::SetDirection(DIRECTION direction)
{
	m_direction = direction;
}

void Enemy::UpdateAnimation()
{
	switch (m_state)
	{
	case PlayerState::Idle:
		SetFlipbook(m_idleFlipbook[m_direction]);
		break;
	case PlayerState::Move:
		SetFlipbook(m_moveFlipbook[m_direction]);
		break;
	case PlayerState::Skill:
		SetFlipbook(m_skillFlipbook[m_direction]);
		break;
	}
}

bool Enemy::HasReachedDestination()
{
	return false;
}

bool Enemy::CanGo(PosInt cellPos)
{
	return false;
}

void Enemy::SetCellPos(PosInt cellPos, bool teleport)
{
	m_cellPos = cellPos;

	InGameScene* scene = dynamic_cast<InGameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	if (!scene) return;

	_destPos = scene->ConvertPos(m_cellPos);

	if (teleport) _pos = _destPos;
}

void Enemy::GetDirectionToPlayer()
{
	float dx = m_player->GetPos().X - m_cellPos.X;
	float dy = m_player->GetPos().Y - m_cellPos.Y;
	float angle = atan2(dy, dx); // 플레이어를 향하는 각도 계산

	// 이동
	m_cellPos.X += m_speed.X * cos(angle);
	m_cellPos.Y += m_speed.Y * sin(angle);
}
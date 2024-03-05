#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"

CameraComponent::CameraComponent()
{

}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::BeginPlay()
{

}

void CameraComponent::TickComponent()
{
	if (!m_Owner) return;

	Position pos = m_Owner->GetPos();

	// TEMP
	pos.X = ::clamp(pos.X, 400.f, 3024.f - 400.f);
	pos.Y = ::clamp(pos.Y, 300.f, 2064.f - 300.f);

	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{

}


#include "pch.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider() : Collider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::BeginPlay()
{
	Super::BeginPlay();


}

void SphereCollider::TickComponent()
{
	Super::TickComponent();


}

void SphereCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (m_ShowDebug == false)
		return;

	Position cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Position pos = GetOwner()->GetPos();
	pos.X -= (cameraPos.X - GwinSizeX * .5f);
	pos.Y -= (cameraPos.Y - GwinSizeY * .5f);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawCircle(hdc, pos, _radius);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBoxToSphere(static_cast<BoxCollider*>(other), this);
	case ColliderType::Sphere:
		return CheckCollisionSphereToSphere(this, static_cast<SphereCollider*>(other));
	}
	return false;
}

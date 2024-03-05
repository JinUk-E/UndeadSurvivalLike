#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();


}

void BoxCollider::TickComponent()
{
	Super::TickComponent();


}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	Position cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Position pos = GetOwner()->GetPos();
	pos.X -= (cameraPos.X - GwinSizeX * .5f);
	pos.Y -= (cameraPos.Y - GwinSizeY * .5f);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, _size.X, _size.Y);
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBoxToBox(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionBoxToSphere(this, static_cast<SphereCollider*>(other));
	}

	return false;
}

RECT BoxCollider::GetRect()
{
	Position pos = GetOwner()->GetPos();
	Position size = GetSize();

	RECT rect =
	{
		(int32)(pos.X - (size.X * .5f)),
		(int32)(pos.Y - (size.Y * .5f)),
		(int32)(pos.X + (size.X * .5f)),
		(int32)(pos.Y + (size.Y * .5f))
	};

	return rect;
}

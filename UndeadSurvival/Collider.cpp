#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Actor.h"

Collider::Collider(ColliderType colliderType) : m_ColliderType(colliderType)
{

}

Collider::~Collider()
{

}

void Collider::BeginPlay()
{

}

void Collider::TickComponent()
{

}

void Collider::Render(HDC hdc)
{

}

bool Collider::CheckCollision(Collider* other)
{
	uint8 layer = other->GetCollisionLayer();
	if (m_CollisionFlag & (1 << layer))
		return true;

	return false;
}

// https://m.blog.naver.com/winterwolfs/10165506488
bool Collider::CheckCollisionBoxToBox(BoxCollider* box1, BoxCollider* box2)
{
	RECT r1 = box1->GetRect();
	RECT r2 = box2->GetRect();
	RECT intersect = {};

	return ::IntersectRect(&intersect, &r1, &r2);
}

bool Collider::CheckCollisionBoxToSphere(BoxCollider* box, SphereCollider* sphere)
{
	return false;
}

bool Collider::CheckCollisionSphereToSphere(SphereCollider* sphere1, SphereCollider* sphere2)
{
	Position p1 = sphere1->GetOwner()->GetPos();
	float r1 = sphere1->GetRadius();

	Position p2 = sphere2->GetOwner()->GetPos();
	float r2 = sphere2->GetRadius();

	Position dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	m_CollisionFlag |= (1 << layer);
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	m_CollisionFlag &= ~(1 << layer);
}

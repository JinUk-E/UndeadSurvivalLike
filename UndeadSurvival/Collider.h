#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType type);
	virtual ~Collider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	ColliderType GetColliderType() { return m_ColliderType; }
	void SetShowDebug(bool show) { m_ShowDebug = show; }

	static bool CheckCollisionBoxToBox(BoxCollider* box1, BoxCollider* box2);
	static bool CheckCollisionSphereToSphere(SphereCollider* sphere1, SphereCollider* sphere2);
	static bool CheckCollisionBoxToSphere(BoxCollider* box, SphereCollider* sphere);

	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { m_CollisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayer() { return m_CollisionLayer; }

	void ResetCollisionFlag() { m_CollisionFlag = 0; }
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void SetCollisionFlag(uint32 flag) { m_CollisionFlag = flag; }
	uint32 GetCollisionFlag() { return m_CollisionFlag; }


	unordered_set<Collider*> _collisionMap;

protected:
	ColliderType m_ColliderType{};
	bool m_ShowDebug{true};

	// 자신에 대한 식별을 위한 레이어
	COLLISION_LAYER_TYPE m_CollisionLayer{COLLISION_LAYER_TYPE_OBJECT};
	// 충동 대상에 대한 식별을 위한 레이어
	uint32 m_CollisionFlag{ 0xFFFFFFFF };

};


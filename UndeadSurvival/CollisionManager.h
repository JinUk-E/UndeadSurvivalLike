#pragma once

class Collider;

class CollisionManager
{
	CREATE_SINGLETONS(CollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

private:
	vector<Collider*> m_colliders;
};


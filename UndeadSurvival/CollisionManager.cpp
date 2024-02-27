#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init(){}

void CollisionManager::Update()
{
	vector<Collider*>& colliders = m_colliders;

	for (int i = 0; i < colliders.size(); i++)
	{
		for (int j = i + 1; j < colliders.size(); j++)
		{
			Collider* src = colliders[i];
			Collider* dst = colliders[j];

			if (src->CheckCollision(dst))
			{
				if (src->_collisionMap.contains(dst)) continue;
				else
				{
					src->GetOwner()->OnCollisionEnter2D(src, dst);
					dst->GetOwner()->OnCollisionEnter2D(dst, src);
					src->_collisionMap.insert(dst);
					dst->_collisionMap.insert(src);
				}
			}
			else
			{
				if (src->_collisionMap.contains(dst))
				{
					src->GetOwner()->OnCollisionExit2D(src, dst);
					dst->GetOwner()->OnCollisionExit2D(dst, src);
					src->_collisionMap.erase(dst);
					dst->_collisionMap.erase(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	m_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = std::remove(m_colliders.begin(), m_colliders.end(), collider);
	m_colliders.erase(it, m_colliders.end());
}
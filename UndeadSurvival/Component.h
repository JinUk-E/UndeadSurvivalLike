#pragma once

class Actor;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void BeginPlay() {}
	virtual void TickComponent() {}
	virtual void Render(HDC hdc) {}

	void SetOwner(Actor* owner) { m_Owner = owner; }
	Actor* GetOwner() { return m_Owner; }

protected:
	Actor* m_Owner;
};
#pragma once

class Actor;

class Component
{
public:
	Component(Actor* owner);
	virtual ~Component();

	virtual void BeginPlay() {}
	virtual void TickComponent() {}
	virtual void Render(HDC hdc) {}

	void SetOwner(Actor* owner) { mOwner = owner; }
	Actor* GetOwner() { return mOwner; }

protected:
	Actor* mOwner;
};


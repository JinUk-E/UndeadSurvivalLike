#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	for(Component* component : _components) component->BeginPlay();
}

void Actor::Tick()
{
	for (Component* component : _components) component->TickComponent();
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components) component->Render(hdc);
}

void Actor::ADDComponent(Component* component)
{
	if(!component) return;

	component->SetOwner(this);
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	if (!component) return;

	auto iter = std::find(_components.begin(), _components.end(), component);
	if (iter == _components.end()) return;
	
	_components.erase(iter);
}

Component* Actor::GetCollider()
{
	for (Component* component : _components)
	{
		if (dynamic_cast<Collider*>(component)) return component;
	}
	return nullptr;
}

void Actor::OnCollisionEnter2D(Collider* self, Collider* other) 
{

}

void Actor::OnCollisionExit2D(Collider* self, Collider* other)
{

}
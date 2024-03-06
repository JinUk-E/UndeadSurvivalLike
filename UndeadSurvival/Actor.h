#pragma once
class Component;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void SetPos(Position pos) { _pos = pos; }
	Position GetPos() { return _pos; }

	void SetLayerType(LAYER_TYPE layerType) { _layerType = layerType; }
	LAYER_TYPE getLayerType() { return _layerType; }

	void ADDComponent(Component* component);
	void RemoveComponent(Component* component);

	Component* GetCollider();
	
	virtual void OnCollisionEnter2D(Collider* self, Collider* other);
	virtual void OnCollisionExit2D(Collider* self, Collider* other);

protected:
	Position _pos{0,0};
	Position _destPos{0,0};
	LAYER_TYPE _layerType{LAYER_TYPE::LAYER_OBJECT};
	vector<Component*> _components{};
};


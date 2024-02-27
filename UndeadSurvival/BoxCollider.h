#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
	using Super = Collider;
public:
	BoxCollider();
	virtual ~BoxCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	Position GetSize() { return _size; }
	void SetSize(Position size) { _size = size; }

	RECT GetRect();

private:
	Position _size{};
};


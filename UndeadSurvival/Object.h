#pragma once
class Object
{
public:
	Object(ObjectType type);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	ObjectType GetType() { return _type; }
	Position GetPos() { return _pos; }
	void SetPos(Position pos) { _pos = pos; }
	float GetRadius() { return _radius; }


protected:
	ObjectType _type{ObjectType::None};
	MoveDir _dir{MoveDir::Right};
	Stat _stat{};
	Position _pos{};
	float _radius{0.0f};
};


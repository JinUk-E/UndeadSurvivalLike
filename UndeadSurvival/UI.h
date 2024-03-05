#pragma once
class UI
{
public:
	UI();
	virtual ~UI();

	virtual void Begin() {};
	virtual void Tick() {};
	virtual void Render(HDC hdc) {};

	void SetPos(Position pos) { m_pos = pos; }
	Position GetPos() { return m_pos; }

	RECT GetRect() {};
	bool IsMouseOn() {};

protected:
	Position m_pos{400,300};
	PosInt m_size{100,100};

};

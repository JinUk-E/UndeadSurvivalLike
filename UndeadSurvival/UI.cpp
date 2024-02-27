#include "pch.h"
#include "UI.h"
#include "InputManager.h"

UI::UI(){}
UI::~UI(){}

void UI::Begin(){}
void UI::Tick() {}
void UI::Render(HDC hdc) {}

RECT UI::GetRect() {
	RECT rect = 
	{
		m_pos.X - m_size.X * .5,
		m_pos.Y - m_size.Y * .5,
		m_pos.X + m_size.X * .5,
		m_pos.Y + m_size.Y * .5
	};
	return rect;
}

bool UI::IsMouseOn()
{
	RECT rect = GetRect();
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	if (mousePos.x > rect.left && mousePos.x < rect.right &&
		mousePos.y > rect.top && mousePos.y < rect.bottom)
		return true;
	else return false;
}

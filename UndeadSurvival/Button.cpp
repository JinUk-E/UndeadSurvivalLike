#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);
}

void Button::Tick()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseOn())
	{
		if (GET_SINGLE(InputManager)->IsKeyDown(KeyType::LeftMouse))
		{
			SetButtonState(BS_Pressed);
			// OnPressed
		}
		else
		{
			if (_state == BS_Pressed)
			{
				SetButtonState(BS_Clicked);
				// OnClicked
				if (_onClick) _onClick();
			}
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	if (_currentSprite)
	{
		::TransparentBlt(hdc,
			(int32)m_pos.X - m_size.X * .5f,
			(int32)m_pos.Y - m_size.Y * .5f,
			m_size.X,
			m_size.Y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().X,
			_currentSprite->GetPos().Y,
			_currentSprite->GetSize().X,
			_currentSprite->GetSize().Y,
			_currentSprite->GetTransparent());
	}
	else
	{
		Utils::DrawRect(hdc, m_pos, m_size.X, m_size.Y);
	}
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state]) SetCurrentSprite(_sprites[state]);
}

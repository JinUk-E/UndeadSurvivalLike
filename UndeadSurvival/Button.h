#pragma once
#include "UI.h"

class Sprite;

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetSize(PosInt size) { m_size = size;}
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(ButtonState state, Sprite* sprite) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

	template<typename T>
	void AddClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]() { (owner->*func)(); };
	}

	// �Լ� ������ + �Լ� ��ü
	std::function<void(void)> _onClick{ nullptr };

protected:
	Sprite* _currentSprite{ nullptr };
	Sprite* _sprites[ButtonState::BS_MaxCount]{}; // ��ư ���¿� ���� ��������Ʈ
	ButtonState _state{ ButtonState::BS_Default };
	float _sumTime{ 0.f };
};


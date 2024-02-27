#pragma once
#include "UI.h"
class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void AddChild(UI* child);
	void RemoveChild(UI* child);

private:
	vector<UI*> _children;
};


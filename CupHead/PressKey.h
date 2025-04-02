#pragma once
#include "UIBase.h"
class PressKey : public UIBase
{
public:
	PressKey();
	virtual ~PressKey();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	RECT RC;
	float Scale;
	float Speed;
	int Dir;
};


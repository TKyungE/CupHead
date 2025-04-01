#pragma once
#include "UIBase.h"
class StartBtn : public UIBase
{
public:
	StartBtn();
	virtual ~StartBtn();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};


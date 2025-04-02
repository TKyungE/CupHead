#pragma once
#include "UIBase.h"

class Image;
class LogoBackground : public UIBase
{
public:
	LogoBackground();
	virtual ~LogoBackground();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};


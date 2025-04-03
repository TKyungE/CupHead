#pragma once
#include "UIBase.h"

class Image;
class UIBackground : public UIBase
{
public:
	UIBackground();
	virtual ~UIBackground();

	void Init(string InKey);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};


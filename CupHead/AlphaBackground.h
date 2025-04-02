#pragma once
#include "UIBase.h"

class Image;
class AlphaBackground : public UIBase
{
public:
	AlphaBackground();
	virtual ~AlphaBackground();

	void Init(float InAlphaSpeed);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	float AlphaSpeed;
	float Alpha;
};

#pragma once
#include "UIBase.h"

class Image;
class ScreenFX : public UIBase
{
public:
	ScreenFX();
	virtual ~ScreenFX();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void UpdateFrame() override;

private:
	vector<Image*> Images;
};


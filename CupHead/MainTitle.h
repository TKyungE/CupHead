#pragma once
#include "UIBase.h"

class Image;
class MainTitle : public UIBase
{
public:
	MainTitle();
	virtual ~MainTitle();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

private:
	Image* BackGround;
};


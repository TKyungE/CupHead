#pragma once
#include "UIBase.h"
class ReadyWallop : public UIBase
{
public:
	ReadyWallop();
	virtual ~ReadyWallop();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};


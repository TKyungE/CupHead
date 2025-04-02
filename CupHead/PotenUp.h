#pragma once
#include "UIBase.h"
class PotenUp : public UIBase
{
public:
	PotenUp();
	virtual ~PotenUp();

	void Init(float InX);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};


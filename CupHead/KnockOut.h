#pragma once
#include "UIBase.h"

class KnockOut : public UIBase
{
public:
	KnockOut();
	virtual ~KnockOut();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};


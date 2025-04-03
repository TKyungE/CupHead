#pragma once
#include "Pawn.h"

class SagittariusArrow : public Pawn
{
public:
	SagittariusArrow(FPOINT pos,FPOINT size);
	virtual ~SagittariusArrow() = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move();
};


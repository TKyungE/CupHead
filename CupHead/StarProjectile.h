#pragma once
#pragma once
#include "Pawn.h"

class StarProjectile : public Pawn
{
public:
	StarProjectile();
	virtual ~StarProjectile();

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

	float LookAngle;
	float MoveValue;
	float SinValue;
};


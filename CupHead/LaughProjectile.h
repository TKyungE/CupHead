#pragma once
#include "Pawn.h"

class LaughProjectile : public Pawn
{
public:
	LaughProjectile();
	virtual ~LaughProjectile();

public:
	void Init(FPOINT _Pos);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

	float LookAngle;
	float MoveValue;
	float SinValue;
};


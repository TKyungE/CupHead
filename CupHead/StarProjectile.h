#pragma once
#pragma once
#include "Pawn.h"

enum class StarType
{
	STARTYPE_A,
	STARTYPE_B,
	STARTYPE_C,
	STARTYPE_END
};

class StarProjectile : public Pawn
{
public:
	StarProjectile();
	StarProjectile(StarType _Type);
	virtual ~StarProjectile();

public:
	virtual void Init() override;
	void Init(FPOINT _Pos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

	float LookAngle;
	float MoveValue;
	float SinValue;
};


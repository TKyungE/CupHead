#pragma once
#include "Pawn.h"
class PlayerFallMissile : public Pawn
{
public:
	PlayerFallMissile();
	virtual ~PlayerFallMissile();

public:
	void Init(FPOINT _Pos);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	float MoveTime;
	float Gravity;
	FPOINT InitPos;
};


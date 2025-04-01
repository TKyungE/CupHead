#pragma once
#include "PlayerMissile.h"
class PlayerFallMissile : public PlayerMissile
{
public:
	PlayerFallMissile();
	virtual ~PlayerFallMissile();

public:
	virtual void Init(FPOINT _Pos, int _Damage) override;
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


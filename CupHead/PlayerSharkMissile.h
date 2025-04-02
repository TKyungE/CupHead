#pragma once
#include "PlayerMissile.h"
class PlayerSharkMissile : public PlayerMissile
{
public:
	PlayerSharkMissile();
	virtual ~PlayerSharkMissile();

public:
	virtual void Init(FPOINT _Pos, int _Damage) override;
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateFrame() override;
	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	bool IsLoop;
	float StopTime;
	float StopMaxTime;
};


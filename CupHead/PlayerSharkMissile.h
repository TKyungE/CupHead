#pragma once
#include "Pawn.h"
class PlayerSharkMissile : public Pawn
{
public:
	PlayerSharkMissile();
	virtual ~PlayerSharkMissile();

public:
	void Init(FPOINT _Pos);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateFrame() override;
	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	bool IsLoop;
};


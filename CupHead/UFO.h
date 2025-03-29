#pragma once
#include "Pawn.h"

class UFOBeam;
class UFO : public Pawn
{
public:
	UFO();
	virtual ~UFO() = default;

	void Init(FPOINT pos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

	void Attack();
private:
	UFOBeam* UFOBeamWeapon;
	bool bAttack;
};


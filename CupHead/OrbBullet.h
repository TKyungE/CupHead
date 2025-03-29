#pragma once
#include "Pawn.h"
class OrbBullet : public Pawn
{
public:
	OrbBullet(FPOINT InPos);
	virtual ~OrbBullet() = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
};

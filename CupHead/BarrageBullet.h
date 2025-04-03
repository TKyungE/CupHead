#pragma once
#include "Character.h"
class BarrageBullet : public Character
{
public:
	BarrageBullet();
	virtual ~BarrageBullet();

public:
	void Init(FPOINT _Pos, float _Angle, float _DeltaAngle, float _LIfe);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	void UpdateAngle();

private:
	float Angle;
	float DeltaAngle;

	float ElapsedTime;
	float Life;
};


#pragma once
#include "Character.h"

class SagittariusStar2 : public Character
{
public:
	SagittariusStar2();
	virtual ~SagittariusStar2() = default;

	void Init(string InKey, float InX, float InY, float InSpeed);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	void TrailUpdate();

private:
	float Angle;
	float ImageSize;
	FPOINT TrailPos;

	string TrailImages[3];	

};


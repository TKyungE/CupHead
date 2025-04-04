#pragma once
#include "Character.h"
class SagittariusStar : public Character
{
private:
	enum class EStarState : uint8_t
	{
		Fire,
		Guided,
		Done,
		Dead,
		End
	};
public:
	SagittariusStar(FPOINT InPos,float InGuidedTime, float InAngle);
	virtual ~SagittariusStar() = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	void Fire();
	void Guided();
	void Done();
	void Dead();

	float SmoothAngle(float currentAngle, float targetAngle, float maxAngleSpeed);
	float NoramlizeAngle(float angle);

	void EffectInit();
	void TrailUpdate();
private:
	EStarState State;
	float CurrentTime;
	float GuidedTime;
	float Angle;
	FPOINT StartPos;
	FPOINT TrailPos;

	float AngularVelocity;
	float maxAngularAcceleration;
	float maxAngularVelocity;
	float friction;

	float ImageSize;
	string TrailImages[3];
};


#pragma once
#include "Character.h"

class Image;
class SagittariusCloud;
class Sagittarius : public Character
{
private:
	enum class ESagittariusState : uint8_t
	{
		Idle,
		Attack,
		End
	};
public:
	Sagittarius();
	virtual ~Sagittarius() = default;

	void Init(FPOINT InPos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	void Idle();
	void Attack();
private:
	SagittariusCloud* Cloud;
	ESagittariusState State;
	float Angle;
	float AngleSpeed;

	float CurrnetTime;
	float AttackTime;
	bool bAttack;
};


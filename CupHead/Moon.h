#pragma once
#include "Character.h"

class Collider;
class Moon : public Character
{
private:
	enum class EMoonState : uint8_t
	{
		Idle,
		Attack,
		Dead,
		End
	};
public:
	Moon();
	virtual ~Moon() = default;

public:
	void Init(int _Hp);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void TakeDamage(int damage = 0) override;

private:
	void Idle();
	void Attack();
	void Dead();

	void UFOSpawn();
	void EffectInit();

private:
	EMoonState State;
	Collider* ColliderComponent;

	float CurrentTime;

	float AttackTime;
	int CurrentAttackCount;
	int AttackCount;

	float UFOSpawnTime;

	float DeadEffectTime;
};


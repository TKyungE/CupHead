#pragma once
#include "Pawn.h"

enum class OrbState : uint8_t
{
	Idle,
	MoveUp,
	MoveDown,
	Attack,
	Dead,
	End
};

class Collider;
class Orb : public Pawn
{
private:
	enum DIRECTION {DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_END};
public:
	Orb(FPOINT InPos, float InSize);
	virtual ~Orb() = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

	void SetState(OrbState InState) { State = InState; }
private:
	void Idle();
	void MoveUp();
	void MoveDown();
	void Attack();
	void Dead();

	void InitRandom();
	void RandomAttackPosition();
	void RandomDir();

	void ResetFrame();
private:
	OrbState State;
	Collider* OrbCollider;
	float StateChangeTime;
	FPOINT AttackPosition;
	DIRECTION Dir;
	bool bFlip;
};


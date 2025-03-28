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

class Orb : public Pawn
{
public:
	Orb(FPOINT InPos, FPOINT InSize);
	virtual ~Orb() = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move();

private:
	void Idle();
	void MoveUp();
	void MoveDown();
	void Attack();
	void Dead();

	void SetState(OrbState InState) { State = InState; }
private:
	OrbState State;
	float StateChangeTime;
};


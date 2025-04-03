#pragma once
#include "Pawn.h"
class PlayerMissile : public Pawn
{
public:
	PlayerMissile();
	virtual ~PlayerMissile();

public:
	virtual void Init(FPOINT _Pos, int _Damage);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

public:
	inline int GetDamage() const { return Damage; };
	inline void SetDamage(int _Damage) { Damage = _Damage; };

protected:
	int Damage;
};


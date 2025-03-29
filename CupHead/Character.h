#pragma once
#include "Pawn.h"
class Character : public Pawn
{
public:
	Character();
	virtual ~Character();

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(float damage = 0.f) override;

	
	inline void SetHp(int _Hp) { Hp = _Hp; }
	inline int GetHp() const { return Hp; }

	inline void SetMaxHp(int _MaxHp) { MaxHp = _MaxHp; }
	inline int GetMaxHp() const { return MaxHp; }

protected:
	int Hp;
	int MaxHp;
	
};


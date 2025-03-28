#pragma once
#include "Actor.h"

class Pawn : public Actor
{
public:
	Pawn();
	virtual ~Pawn();

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() {};

	inline void SetSpeed(int _Speed) { Speed = _Speed; }
	inline int GetSpeed() const { return Speed; }

protected:
	float Speed;
};


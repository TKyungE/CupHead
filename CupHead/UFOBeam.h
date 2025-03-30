#pragma once
#include "Actor.h"

class Collider;
class UFOBeam : public Actor
{
public:
	UFOBeam();
	virtual ~UFOBeam() = default;

	virtual void Init() override;
	virtual void Release() override;
	void Update(FPOINT parentPos);
	virtual void Render(HDC hdc) override;

	void Attack();
private:
	Collider* Collider;
};


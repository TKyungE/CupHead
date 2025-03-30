#pragma once
#include "Actor.h"

class Collider;
class UFOBeam : public Actor
{
public:
	UFOBeam();
	virtual ~UFOBeam() = default;

	void Init(GameObject* InOwner, FPOINT InPivot);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Attack();
private:
	GameObject* Owner;
	Collider* Collider;
	FPOINT Pivot;
};


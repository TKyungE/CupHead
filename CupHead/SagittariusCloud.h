#pragma once
#include "Actor.h" 

class SagittariusCloud : public Actor
{
public:
	SagittariusCloud();
	virtual ~SagittariusCloud() = default;

	void Init(GameObject* InOwner, FPOINT InPivot = {0.f,0.f});
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	GameObject* Owner;
	FPOINT Pivot;
};


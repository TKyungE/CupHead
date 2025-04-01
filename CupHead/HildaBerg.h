#pragma once
#include "GameObject.h"
class HildaBerg : public GameObject
{
public:
	HildaBerg();
	virtual ~HildaBerg();

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void TakeDamage(int damage = 0) {};

	FPOINT GetPos() const { return pos; }
	bool IsDead() const { return bDead; }

	void SetDead(bool bDead) { this->bDead = bDead; }

private:
	void ChangeForm();

private:
	GameObject* HildaForm;
	int Phase;
};


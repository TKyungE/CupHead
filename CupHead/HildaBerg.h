#pragma once
#include "GameObject.h"

class Character;
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

	int GetTotalHp() const;
	int GetCurrentFormHp() const;

private:
	void ChangeForm();
	void SpawnEnemy();

private:
	Character* HildaForm;
	int Phase;
	float Angle;

	float ElapsedSpawnTime;
	float SpawnCoolTime;

	int HpList[6];
};


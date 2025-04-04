#pragma once
#include "GameObject.h"

struct FHildaBergData
{
	int Phase;
	int TotalHp;
	int CurrentHp;
	int HpList[6];
};

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
	int GetCurrentHp() const;

	void ChangePhaseByInput(int _Phase); // for debug

private:
	void ChangeForm();
	void SpawnEnemy();
	void ProcessInput();

private:
	Character* HildaForm;
	int Phase;
	float Angle;

	float ElapsedSpawnTime;
	float SpawnCoolTime;

	int HpList[6];

	FHildaBergData HlidaBergData;
};


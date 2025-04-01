#pragma once
#include "Character.h"

namespace HildaBlimpInfo
{
	enum EState
	{
		INTRO,
		IDLE,
		SHOOT,
		TORNADO,
		DASH,
		SUMMON,
		SUMMONRECOVER,
		STATE_END
	};

	extern string states[EState::STATE_END];
}

class HildaBlimp : public Character
{
public:
	HildaBlimp(int phase);
	virtual ~HildaBlimp();

	void Init(FPOINT InPos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateFrame() override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

private:
	void UpdateState();
	void SetState(HildaBlimpInfo::EState NewState);
	
	void ShootPaternByPhase();
	void ShootHa();
	void ShootTornado();

	void Dash();
	void DashRecover();

	// 나중에 옮기든지..
	float GetWidth();
	float GetHeight();

private:
	int Phase;

	float Angle;
	float AngleSpeed;

	HildaBlimpInfo::EState CurState;
	vector<pair<string, float>> AnimData;
	bool IsAnimEnd;

	float ElapsedShootTime;
	float ShootCoolTime;

	int HaShootCnt;
	int HaMaxShootCnt;
};


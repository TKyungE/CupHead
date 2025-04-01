#pragma once
#include "Character.h"

namespace TaurusInfo
{
	enum EState
	{
		IDLE,
		ATTACK,
		STATE_END
	};

	extern string states[EState::STATE_END];
}

class Collider;
class Taurus : public Character
{
public:
	Taurus();
	virtual ~Taurus();

public:
	void Init(FPOINT _Pos, float _Angle = 0);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateFrame() override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

	virtual float GetMoveAngle() override { return Angle; }

private:
	void UpdateState();
	void SetState(TaurusInfo::EState NewState);

	void Dash();
	void Recover();

	// 나중에 옮기든지..
	float GetWidth();
	float GetHeight();

private:
	float Angle;
	float AngleSpeed;

	TaurusInfo::EState CurState;
	vector<pair<string, float>> AnimData;
	bool IsAnimEnd;

	float ElapsedAttackTime;
	float AttackCoolTime;

	FPOINT PosBefore;

	Collider* AttackCollider;
};


#pragma once
#include "Character.h"

namespace BlimpEnemyInfo
{
	enum EState
	{
		IDLE,
		ATTACK,
		TURN,
		STATE_END
	};

	extern string states[EState::STATE_END];

	enum EColor
	{
		PURPLE,
		GREEN,
		COLOR_END,
	};

	extern string colors[EColor::COLOR_END];
}

class BlimpEnemy : public Character
{
public:
	BlimpEnemy();
	virtual ~BlimpEnemy();

	void Init(BlimpEnemyInfo::EColor _Color, int _BulletNum);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateFrame() override;

	virtual void Move() override;

private:
	void UpdateState();

	void FireBullet();

	void SetState(BlimpEnemyInfo::EState NewState, bool AnimReverse);

	// 나중에 옮기든지..
	float GetWidth();
	float GetHeight();

private:
	float Dx;
	float Dy;

	string Color;
	int BulletNum;
	bool IsFired;

	BlimpEnemyInfo::EState CurState;
	vector<pair<string, float>> AnimData;
	bool IsAnimEnd;
	bool IsAnimReverse;
};


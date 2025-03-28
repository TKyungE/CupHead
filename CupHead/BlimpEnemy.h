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

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	inline void SetColor(string _Color) { Color = _Color; }
	inline string GetColor() const { return Color; }

	inline void SetBulletNum(int _BulletNum) { BulletNum = _BulletNum; }
	inline int GetBulletNum() const { return BulletNum; }

	void SetState(BlimpEnemyInfo::EState NewState);

private:
	string Color;
	int BulletNum;
	BlimpEnemyInfo::EState CurState;
	vector<pair<string, float>> AnimData;
};


#pragma once
#include "Pawn.h"

namespace TornadoInfo
{
	enum EState
	{
		INTRO,
		ATTACK,
		STATE_END
	};

	extern string states[EState::STATE_END];
}

class Tornado : public Pawn
{
public:
	Tornado();
	virtual ~Tornado();

	void Init(FPOINT _pos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateFrame() override;

	virtual void Move() override;

	void UpdateState();
	void SetState(TornadoInfo::EState NewState, bool AnimReverse);

	// 나중에 옮기든지..
	float GetWidth();
	float GetHeight();

private:
	float Dx;
	float Angle;

	float ChaseTime;
	float MaxChaseTime;

	TornadoInfo::EState CurState;
	vector<pair<string, float>> AnimData;
	bool IsAnimEnd;
	bool IsAnimReverse;
};


#pragma once
#include "UIBase.h"
class TrumpCard : public UIBase
{
public:
	TrumpCard();
	virtual ~TrumpCard();

	void Init(FPOINT InPos, float InMaxCount);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void UpdateFrame() override;

	bool IsTurn() const { return bTurn; }
	void SetCurrentCount(int InCount) { CurrentCount = InCount; }
	void SetbTurn(bool InbTurn) { 
		bTurn = InbTurn;
		FrameTime = 0.f;
	}
	

private:
	FPOINT DefaultPos;
	int MaxCount;
	int CurrentCount;
	int MaxY;

	bool bTurn;
	int FrameDir;
};


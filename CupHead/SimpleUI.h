#pragma once
#include "UIBase.h"
class SimpleUI : public UIBase
{
public:
	SimpleUI();
	virtual ~SimpleUI();

	void Init(string InKey, float FrameSpeed, float InX, float InY, int InLifeCount = -1,bool InPingPong = false,bool InRepeat = true);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void UpdateFrame() override;
private:
	bool bRepeat;
	bool bPingPong;
	int FrameDir;

	int CurrentLifeCount;
	int LifeCount;
};


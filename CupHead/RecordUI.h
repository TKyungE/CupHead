#pragma once
#include "UIBase.h"
class RecordUI : public UIBase
{
public:
	RecordUI();
	virtual ~RecordUI();

	void Init(string InKey,float InX, float InY, float InRecordTime, float InDelayTime = 3.f, int InFrameCount = 5);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void UpdateFrame() override;

private:
	float CurrentTime;
	float DelayTime;
	int CurrentFrameCount;
	int FrameCount;

	float RecordTime;
};


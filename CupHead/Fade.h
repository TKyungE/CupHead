#pragma once
#include "UIBase.h"

enum class EFadeMode : uint8_t
{
	FadeIn,
	FadeOut,
	End
};

class Fade : public UIBase
{
public:
	Fade();
	virtual ~Fade();

	void Init(EFadeMode InFadeMode);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void UpdateFrame() override;

	void SetFadeMode(EFadeMode InFadeMode);
private:
	EFadeMode FadeMode;
	int FrameDir;
	float Alpha;
};


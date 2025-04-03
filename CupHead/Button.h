#pragma once
#include "UIBase.h"

enum class EButtonType : uint8_t
{
	ReTry,
	Exit,
	End
};

class Button : public UIBase
{
public:
	Button();
	virtual ~Button();

	void Init(string InKey,float InX, float InY,EButtonType InButtonType);
	virtual void Release() override;
	virtual void Update() override;

	void SetHover(bool InHover) { bHover = InHover; }
private:
	EButtonType ButtonType;
	bool bHover;
};


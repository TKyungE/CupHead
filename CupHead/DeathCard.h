#pragma once
#include "UIBase.h"
#include <vector>

class Button;
class DeathCard : public UIBase
{
public:
	DeathCard();
	virtual ~DeathCard();

	void Init(string InKey,float InX, float InY);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	void DeathCardInit();

private:
	bool bFirst;
	vector<Button*> Buttons;
	int CurrentButtonIndex;

};


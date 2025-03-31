#pragma once
#include "UIBase.h"

class Character;
class PlayerHP : public UIBase
{
public:
	PlayerHP();
	virtual ~PlayerHP();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	void HPUpdate();
	void HP1SettingReset();
private:
	Character* Player;
	bool bHP1SettingReset;
};


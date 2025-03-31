#pragma once
#include "Character.h"

class Image;

enum PLAYERSTATE
{
	PLAYER_IDLE, PLAYER_MOVE, PLAYER_ATTACK, PLAYER_END
};

enum UPDOWN
{
	UPDOWN_NONE, UPDOWN_UP, UPDOWN_DOWN, UPDOWN_END
};

class Player : public Character
{

public:
	Player();
	~Player();

	

public:
	virtual void Init() override;
	void Init(FPOINT pos, FPOINT size);
	
	virtual void Release() override;
	virtual void Update() override;
	virtual void UpdateFrame() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;
	virtual void TakeDamage(int damage = 0) override;

	void Action();
	void ImageInit();

	void UpdateInput();
	void UpdateState();
	void EffectTestInit();

	//virtual void TakeDamage(int damage = 0);

private:
	int FrameDir;
	bool IsTranseEnd;
	UPDOWN UpDownState = UPDOWN_NONE;
	PLAYERSTATE PreState;
	PLAYERSTATE CurState;
};


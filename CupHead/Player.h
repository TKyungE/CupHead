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

enum ATTACKTYPE
{
	ATTACK_NORMAL, ATTACK_FALL, ATTACK_SHARK, ATTACK_END
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
	void EffectInit();

	void UpdateInput();
	void UpdateState();
	void UpdateToUpState();
	void UpdateToDownState();
	void UpdateToNoneState();

	void Attack();
	void Fire(ATTACKTYPE _Type);
	void FireNormal();
	void FireFall();
	void FireShark();

	//void UpdateUpDownState();


	//virtual void TakeDamage(int damage = 0);

private:
	int FrameDir;
	int FireCnt;
	float AttackTimes[ATTACK_END];
	float AttackCoolTimes[ATTACK_END];
	float AlphaTime;
	float MaxAlphaTime;
	UPDOWN PreUpDownState;
	UPDOWN CurUpDownState;
	PLAYERSTATE PreState;
	PLAYERSTATE CurState;
	Image* NextImage;


};


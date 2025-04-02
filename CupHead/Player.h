#pragma once
#include "Character.h"

class Image;
class SkillPointManager;

enum PLAYERSTATE
{
	PLAYER_INTRO, PLAYER_IDLE, PLAYER_MOVE, PLAYER_ATTACK, PLAYER_END
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
	void Init(FPOINT pos, FPOINT size);

	virtual void Init() override;
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

	void Intro();

	void UpdateEffect();
	void UpdateTime();
	void UpdateAttackFrame();

	void Attack();
	void Fire(ATTACKTYPE _Type);
	void FireNormal();
	void FireFall();
	void FireShark();
	void ResetFrame();
	void ResetState();

	//void UpdateUpDownState();

public:
	inline int GetDamage() const { return PLAYER_ATTACK == CurState ? Damage : 0 ; };
	inline void SetDamage(int _Damage) { Damage = _Damage; };

	inline float GetSkillPoint() const { return SkillPoint; };
	inline void SetSkillPoint(float _SkillPoint) 
	{ 
		SkillPoint = _SkillPoint;
		SkillPoint = max(MaxSkillPoint, SkillPoint);
	};
	inline void PlusSkillPoint(float _SkillPoint) 
	{ 
		SkillPoint += _SkillPoint;
		SkillPoint = max(MaxSkillPoint, SkillPoint);
	};

private:
	bool IsSharkFire;
	bool IsIntroEnd;
	float IntroAngle;
	float IntroDistance = 0.f;
	FPOINT InitPos;
	FPOINT PrePos;
	int Damage; // 미사일 변신하고 충돌하면 넘길 데미지
	int FrameDir;
	int FireCnt;
	float AttackTimes[ATTACK_END];
	float AttackCoolTimes[ATTACK_END];

	int DustCnt;
	float DustTime;
	float DustCoolTime;
	
	float AlphaTime;
	float MaxAlphaTime;
	UPDOWN PreUpDownState;
	UPDOWN CurUpDownState;
	PLAYERSTATE PreState;
	PLAYERSTATE CurState;
	Image* NextImage;
	SkillPointManager* SkillManager;

private:
	float SkillPoint;
	float MaxSkillPoint;
};


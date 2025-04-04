#include "Player.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "ObjectManager.h"
#include "CommonFunction.h"
#include "PlayerNormalMissile.h"
#include "PlayerFallMissile.h"
#include "PlayerSharkMissile.h"
#include "DeathCard.h"
#include "SkillPointManager.h"
#include "BrokenPiece.h"

Player::Player() :
		IsSharkFire(false),
		IsIntroEnd(false),
		IsIntroStart(false),
		IntroAngle(0.f),
		IntroDistance(0.f),
		InitPos({0.f,0.f}), PrePos({ 0.f,0.f }),
		Damage(5), FrameDir(1), FireCnt(0), 
		DustCnt(0), DustTime(0.f), DustCoolTime(0.15f), DeathUICoolTime(0.f),
		PreUpDownState(UPDOWN_NONE), CurUpDownState(UPDOWN_NONE), 
		PreState(PLAYER_INTRO), CurState(PLAYER_INTRO),
		NextImage(nullptr), SkillManager(nullptr),
		SkillPoint(0), MaxSkillPoint(250)
{
	AttackCoolTimes[ATTACK_NORMAL] = 0.1f;
	AttackCoolTimes[ATTACK_FALL] = 0.5f;
	AttackCoolTimes[ATTACK_SHARK] = 0.5f;
	memcpy(AttackTimes, AttackCoolTimes, sizeof(AttackTimes));
	UseSkillGage[ATTACK_NORMAL] = 0;
	UseSkillGage[ATTACK_FALL] = 0;
	UseSkillGage[ATTACK_SHARK] = 50;

	MaxAlphaTime = 0.5f;
}				  

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Init(FPOINT pos, FPOINT size)
{
	PrePos = InitPos = this->pos = pos;
	this->size = size;
	Speed = 700.f;
	FrameSpeed = 25.f;
	Hp = 8;

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, size, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER);
	
	ImageInit();
	EffectInit();

	SkillManager = new SkillPointManager();
	SkillManager->Init(50, 5);
}

void Player::Release()
{
	if (nullptr != SkillManager)
	{
		delete SkillManager;
		SkillManager = nullptr;
	}
}

void Player::Update()
{
	UpdateTime();
	Move();
	Action();
	UpdateState();
	UpdateSkillPoint();
	UpdateFrame();
}

void Player::UpdateFrame()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	if (PLAYER_ATTACK == CurState)
	{
		UpdateAttackFrame();
		return;
	}

	//if(CurState)
	if (-1 == FrameDir)
	{
		FrameTime += FrameDir * 1.5f * FrameSpeed * DeltaTime; //Gara
	}

	else
	{
		FrameTime += FrameDir * FrameSpeed * DeltaTime;
	}
	
	CurFrameIndex = (int)FrameTime;

	if (-1 == FrameDir && UPDOWN_NONE != CurUpDownState)
	{
		if (0 > CurFrameIndex)
		{
			FrameDir = 1;
			if (nullptr != NextImage)
			{
				image = NextImage;
				NextImage = nullptr;
			}

			if (UPDOWN_UP == CurUpDownState)
			{
				NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_up");
			}

			else if (UPDOWN_DOWN == CurUpDownState)
			{
				NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_down");
			}

			ResetFrame();
		}
	}

	else if (-1 == FrameDir && UPDOWN_NONE == CurUpDownState)
	{
		if (0 > CurFrameIndex)
		{
			FrameDir = 1;
			if (nullptr != NextImage)
			{
				image = NextImage;
				NextImage = nullptr;
			}
			ResetFrame();
		}
	}

	else if (UPDOWN_NONE != CurUpDownState)
	{
		if (CurFrameIndex >= image->GetMaxFrameX())
		{
			if (nullptr != NextImage)
			{
				image = NextImage;
				NextImage = nullptr;
			}
			ResetFrame();
		}
	}

	else if (CurFrameIndex >= image->GetMaxFrameX())
	{
		ResetFrame();
		if (false == IsIntroEnd)
		{
			IsIntroEnd = true;
			CurState = PLAYER_IDLE;
		}
	}
}

void Player::UpdateInput()
{

}

void Player::UpdateState()
{
	if (PreState != CurState)
	{
		switch (PreState)
		{
		case PLAYER_INTRO:
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
			ResetState();
			break;
		case PLAYER_IDLE:
			break;
		case PLAYER_MOVE:
			break;
		case PLAYER_ATTACK:
			IsSharkFire = false;
			CurState = PLAYER_MOVE;
			image = NextImage;
			ResetState();
			ResetFrame();
			break;
		case PLAYER_END:
			break;
		default:
			break;
		}

		switch (CurState)
		{
		case PLAYER_IDLE:
			break;
		case PLAYER_MOVE:
			break;
		case PLAYER_ATTACK:
			if (UPDOWN_UP == CurUpDownState)
			{
				image = ImageManager::GetInstance()->FindImage("cuphead_plane_ex_up");
			}
			else
			{
				image = ImageManager::GetInstance()->FindImage("cuphead_plane_ex_down");
			}
			ResetFrame();
			break;
		case PLAYER_DEAD:
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_ghost");
			NextImage = nullptr;
			ResetFrame();
			break;
		case PLAYER_END:
			break;
		default:
			break;
		}
	}

	PreState = CurState;

	if (CurState == PLAYER_ATTACK)
	{
		switch (CurUpDownState)
		{
		case UPDOWN_UP:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			break;
		case UPDOWN_DOWN:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			break;
		case UPDOWN_NONE:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
			break;
		default:
			break;
		}

		PreUpDownState = CurUpDownState;
		return;
	}

	if (PreUpDownState != CurUpDownState)
	{
		switch (CurUpDownState)
		{
		case UPDOWN_UP:
			UpdateToUpState();
			break;
		case UPDOWN_DOWN:
			UpdateToDownState();
			break;
		case UPDOWN_NONE:
			UpdateToNoneState();
			break;
		default:
			break;
		}

		PreUpDownState = CurUpDownState;
	}
}

void Player::UpdateToUpState()
{
	if (-1 == FrameDir)
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			break;
		case UPDOWN_UP:
			break;
		case UPDOWN_DOWN:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}

	else
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_up");
			FrameDir = 1;
			break;
		case UPDOWN_UP:
			break;
		case UPDOWN_DOWN:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			FrameDir = -1;
			CurFrameIndex = FrameTime = image->GetMaxFrameX();
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}
}

void Player::UpdateToDownState()
{
	if (-1 == FrameDir)
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			break;
		case UPDOWN_UP:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			break;
		case UPDOWN_DOWN:
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}

	else
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_down");
			FrameDir = 1;
			break;
		case UPDOWN_UP:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			FrameDir = -1;
			CurFrameIndex = FrameTime = image->GetMaxFrameX();
			break;
		case UPDOWN_DOWN:
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}
}

void Player::UpdateToNoneState()
{
	switch (PreUpDownState)
	{
	case UPDOWN_NONE:
		break;
	case UPDOWN_UP:
		FrameDir = -1;
		image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
		NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
		CurFrameIndex = FrameTime = image->GetMaxFrameX();
		break;
	case UPDOWN_DOWN:
		FrameDir = -1;
		image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
		NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
		CurFrameIndex = FrameTime = image->GetMaxFrameX();
		break;
	case UPDOWN_END:
		break;
	default:
		break;
	}
}

void Player::Intro()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	if (false == IsIntroStart)
	{
		EffectManager::GetInstance()->AddEffect("shmup_smoke", pos, image->GetMaxFrameX() / FrameSpeed, { -20.f, 20.f }, 1, true, this);
		IsIntroStart = true;
	}

	if (5 >= CurFrameIndex)
	{
		float Temp = 1000.f * DeltaTime * FrameSpeed / image->GetMaxFrameX();
		IntroDistance += Temp;
		pos.x += Temp;
		pos.y += Temp;
		InitPos.y += Temp;
	}

	else if (6 <= CurFrameIndex && 30 >= CurFrameIndex)
	{
		pos.x = InitPos.x + IntroDistance * cosf(DEG_TO_RAD(IntroAngle));
		pos.y = InitPos.y - 0.7f * IntroDistance * sinf(DEG_TO_RAD(IntroAngle));
		IntroAngle += DeltaTime * 300.f * FrameSpeed / image->GetMaxFrameX();
	}

	else
	{
		pos.x += 700.f * DeltaTime * FrameSpeed / image->GetMaxFrameX();
	}
}

void Player::UpdateEffect()
{
	if (DustCoolTime <= DustTime && PrePos.x < pos.x)
	{
		string Key = "AirDust";
		Key += char(++DustCnt) + '0';
		EffectManager::GetInstance()->AddEffect(Key, pos, 0.5f, {-50.f,10.f}/*, 1, true, this*/);
		if (3 <= DustCnt)
		{
			DustCnt = 0;
		}
		DustTime = 0.f;
	}
}

void Player::UpdateTime()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	for (int i = 0; i < ATTACK_END; ++i)
	{
		AttackTimes[i] += DeltaTime;
		AttackTimes[i] = min(AttackCoolTimes[i], AttackTimes[i]);
	}

	AlphaTime -= DeltaTime;
	AlphaTime = max(AlphaTime, 0.f);

	DustTime += DeltaTime;
	DustTime = min(DustTime, DustCoolTime);

	if (PLAYER_DEAD == CurState)
	{
		DeathUICoolTime -= DeltaTime;
		if (0.f >= DeathUICoolTime) // 유령 보여주고 UI 출력하기.
		{
			DeathCard* deathCard = new DeathCard();
			deathCard->Init("death_card_bg", WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f);
			ObjectManager::GetInstance()->AddObject(deathCard, OBJTYPE::OBJ_UI);
			DeathUICoolTime = 1000000.f;
		}
	}
}

void Player::UpdateAttackFrame()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	FrameTime += FrameSpeed * DeltaTime;
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
		ResetFrame();
		CurState = PLAYER_IDLE;
	}
}

void Player::UpdateSkillPoint()
{
	SkillManager->SetSkillPoint(SkillPoint);
	SkillManager->Update();
}

void Player::Attack()
{
	if (false == IsSharkFire)
	{
		if (13 <= CurFrameIndex)
		{
			IsSharkFire = true;
			FireShark();
		}
	}
}

void Player::Dead()
{
}

void Player::Fire(ATTACKTYPE _Type)
{
	if (AttackCoolTimes[_Type] > AttackTimes[_Type])
	{
		return;
	}

	if (ATTACK_SHARK == _Type && UseSkillGage[ATTACK_SHARK] > SkillPoint)
	{
		return;
	}

	if (PLAYER_ATTACK == CurState)
	{
		return;
	}

	switch (_Type)
	{
	case ATTACK_NORMAL:
		FireNormal();
		break;
	case ATTACK_FALL:
		FireFall();
		break;
	case ATTACK_SHARK:
		CurState = PLAYER_ATTACK;
		break;
	}

	SkillPoint -= UseSkillGage[_Type];
}

void Player::FireNormal()
{
	string Key = "plane_shoot_spark_000";
	Key += char(++FireCnt) + '0';
	FPOINT OffsetPos = { 80.f, 5.f };
	EffectManager::GetInstance()->AddEffect(Key, pos, AttackCoolTimes[ATTACK_NORMAL], OffsetPos, 1, true, this);
	AttackTimes[ATTACK_NORMAL] = 0.f;
	FPOINT FirePos = { pos.x + OffsetPos.x , pos.y + OffsetPos.y };

	(0 == FireCnt % 2) ? FirePos.y += 20.f : FirePos.y -= 20.f, FirePos.x += 10.f;

	PlayerNormalMissile* Missile = new PlayerNormalMissile();
	Missile->Init(FirePos, 1);
	ObjectManager::GetInstance()->AddObject(Missile, OBJTYPE::OBJ_PLAYER_WEAPON);

	if (4 <= FireCnt)
	{
		FireCnt = 0;
	}
}

void Player::FireFall()
{
	string Key = "plane_shoot_spark_000";
	Key += char(++FireCnt) + '0';
	FPOINT OffsetPos = { 60.f, 15.f };
	EffectManager::GetInstance()->AddEffect(Key, pos, 0.07f, OffsetPos, 1, true, this);
	AttackTimes[ATTACK_FALL] = 0.f;
	FPOINT FirePos = { pos.x + OffsetPos.x , pos.y + OffsetPos.y };
	PlayerFallMissile* Missile = new PlayerFallMissile();
	Missile->Init(FirePos, 5);
	ObjectManager::GetInstance()->AddObject(Missile, OBJTYPE::OBJ_PLAYER_WEAPON);

	if (4 <= FireCnt)
	{
		FireCnt = 0;
	}
}

void Player::FireShark()
{
	string Key = "plane_shoot_spark_000";
	Key += char(++FireCnt) + '0';
	FPOINT OffsetPos = { 60.f, 15.f };
	EffectManager::GetInstance()->AddEffect(Key, pos, 0.07f, OffsetPos, 1, true, this);
	AttackTimes[ATTACK_SHARK] = 0.f;
	FPOINT FirePos = { pos.x + OffsetPos.x , pos.y + OffsetPos.y };
	PlayerSharkMissile* Missile = new PlayerSharkMissile();
	Missile->Init(FirePos, 3);
	ObjectManager::GetInstance()->AddObject(Missile, OBJTYPE::OBJ_PLAYER_WEAPON);

	if (4 <= FireCnt)
	{
		FireCnt = 0;
	}
}

void Player::ResetFrame()
{
	CurFrameIndex = FrameTime = 0;
	FrameDir = 1;
}

void Player::ResetState()
{
	PreUpDownState = UPDOWN_NONE;
	CurUpDownState = UPDOWN_NONE;
	PreState = PLAYER_IDLE;
	CurState = PLAYER_IDLE;
	NextImage = nullptr;
}

void Player::Render(HDC hdc)
{
	if (image)
	{
		if (0.f < AlphaTime)
		{
			image->FrameRenderAlpha(hdc, pos.x, pos.y, CurFrameIndex, 0, false, 135);
		}

		else
		{
			image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
			AlphaTime = 0.f;
		}
	}
}

void Player::EffectInit()
{
	ImageManager::GetInstance()->AddImage("blimp_enemy_explode", TEXT("Image/CupHead/Hilda Berg/Enemy/Explode/blimp_enemy_explode.bmp"), 4172, 217, 14, 1, true, RGB(255, 0, 255)); 
	ImageManager::GetInstance()->AddImage("blimp_enemy_spark", TEXT("Image/CupHead/Hilda Berg/Enemy/Explode/blimp_enemy_spark.bmp"), 2232, 260, 9, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("blimp_star_fx", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_fx.bmp"), 1120, 70, 8, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("sagg_arrow_fx", TEXT("Image/CupHead/Hilda Berg/Sagittarius/Arrow/Smoke/sagg_arrow_fx.bmp"), 1045, 203, 5, 1, true, RGB(255, 0, 255)); 
	ImageManager::GetInstance()->AddImage("cuphead_plane_hit_fx", TEXT("Image/CupHead/cuphead_plane/Damaged/cuphead_plane_hit_fx.bmp"), 1936, 205, 11, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("cuphead_plane_hit_fx_b", TEXT("Image/CupHead/cuphead_plane/Damaged/cuphead_plane_hit_fx_b.bmp"), 2259, 267, 9, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("schmup_peashot_hit_spark", TEXT("Image/CupHead/cuphead_plane/Shoot/schmup_peashot_hit_spark.bmp"), 568, 73, 8, 1, true, RGB(255, 0, 255));

	//LargeSpark
	ImageManager::GetInstance()->AddImage("LargeSpark", TEXT("Image/CupHead/cuphead_plane/Shoot/LargeSpark.bmp"), 2256, 261, 8, 1, true, RGB(255, 0, 255));

	//LargeFire
	ImageManager::GetInstance()->AddImage("LargeFire", TEXT("Image/CupHead/cuphead_plane/Shoot/LargeFire.bmp"), 1862, 247, 7, 1, true, RGB(255, 0, 255));

	//LargeExplosion
	ImageManager::GetInstance()->AddImage("LargeExplosion", TEXT("Image/CupHead/cuphead_plane/Shoot/LargeExplosion.bmp"), 3926, 298, 13, 1, true, RGB(255, 0, 255));

	//SharkFire
	ImageManager::GetInstance()->AddImage("SharkStartFire", TEXT("Image/CupHead/cuphead_plane/Shoot/SharkStartFire.bmp"), 585, 100, 5, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("SharkLoopFire", TEXT("Image/CupHead/cuphead_plane/Shoot/SharkLoopFire.bmp"), 468, 100, 4, 1, true, RGB(255, 0, 255));

	//Dust
	ImageManager::GetInstance()->AddImage("AirDust1", TEXT("Image/CupHead/cuphead_plane/Idle/AirDust1.bmp"), 377, 27, 13, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("AirDust2", TEXT("Image/CupHead/cuphead_plane/Idle/AirDust2.bmp"), 275, 26, 11, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("AirDust3", TEXT("Image/CupHead/cuphead_plane/Idle/AirDust3.bmp"), 377, 29, 13, 1, true, RGB(255, 0, 255));

	//Smoke
	ImageManager::GetInstance()->AddImage("shmup_smoke", TEXT("Image/CupHead/cuphead_plane/Idle/shmup_smoke.bmp"), 11825, 192, 43, 1, true, RGB(255, 0, 255));

}

void Player::Action()
{
	switch(CurState)
	{
	case PLAYER_INTRO:
		Intro();
		break;
	case PLAYER_IDLE:
		UpdateEffect();
		break;
	case PLAYER_MOVE:
		UpdateEffect();
		break;
	case PLAYER_ATTACK:
		Attack();
		break;
	case PLAYER_DEAD:
		Dead();
		break;
	case PLAYER_END:
		break;
	default:
		break;
	}

	PrePos = pos; // 비행기 앞으로 이동할때만 이펙트 나오자.
}

void Player::ImageInit()
{
	image = ImageManager::GetInstance()->AddImage("cuphead_plane_idle_down",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_idle_down.bmp"),
		440, 104, 4, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_idle_up",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_idle_up.bmp"),
		456, 93, 4, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_trans_down",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_trans_down.bmp"),
		1243, 102, 11, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_trans_up",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_trans_up.bmp"),
		1254, 104, 11, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_ex_down",
		TEXT("Image/CupHead/cuphead_plane/Shoot/cuphead_plane_ex_down.bmp"),
		10056, 367, 24, 1, true, RGB(255, 0, 255));

	// Shark
	image = ImageManager::GetInstance()->AddImage("cuphead_plane_ex_up",
		TEXT("Image/CupHead/cuphead_plane/Shoot/cuphead_plane_ex_up.bmp"),
		10056, 367, 24, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_idle_straight",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_idle_straight.bmp"),
		448, 101, 4, 1, true, RGB(255, 0, 255));

	
	image = ImageManager::GetInstance()->AddImage("cuphead_plane_ghost",
		TEXT("Image/CupHead/cuphead_plane/Damaged/cuphead_plane_ghost.bmp"),
		2544, 150, 24, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_intro",
		TEXT("Image/CupHead/cuphead_plane/cuphead_plane_intro.bmp"),
		7216, 155, 41, 1, true, RGB(255, 0, 255));


	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0001",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0001.bmp"),
		72, 61, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0002",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0002.bmp"),
		73, 62, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0003",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0003.bmp"),
		76, 60, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0004",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0004.bmp"),
		65, 49, 1, 1, true, RGB(255, 0, 255));

	// PlanePiece
	ImageManager::GetInstance()->AddImage(
		"schmup_ch_piece_a",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_ch_piece_a.bmp"),
		424, 55,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_ch_piece_b",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_ch_piece_b.bmp"),
		416, 55,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_ch_piece_c",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_ch_piece_c.bmp"),
		280, 36,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_ch_piece_d",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_ch_piece_d.bmp"),
		288, 36,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_ch_piece_e",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_ch_piece_e.bmp"),
		504, 62,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_gear_a",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_gear_a.bmp"),
		512, 64,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_gear_b",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_gear_b.bmp"),
		264, 36,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_gear_c",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_gear_c.bmp"),
		504, 68,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"schmup_gear_d",
		TEXT("Image\\CupHead\\cuphead_plane\\PlanePiece\\schmup_gear_d.bmp"),
		448, 55,
		8, 1,
		true, RGB(255, 0, 255));
}

void Player::Move()
{
	if (false == IsIntroEnd)
	{
		CurState = PLAYER_INTRO;

		return;
	}
	
	if (PLAYER_DEAD == CurState)
	{
		pos.y -= 50.f * TimerManager::GetInstance()->GetDeltaTime(); // 임의값
		return;
	}

	if (PLAYER_ATTACK != CurState)
	{
		CurState = PLAYER_IDLE;
	}
	
	KeyManager* keyManager = KeyManager::GetInstance();
	if (keyManager)
	{
		FPOINT position = { 0.f,0.f };
		if (keyManager->IsStayKeyDown('J')) // Test, 원래 키는 뭐지
		{
			Fire(ATTACK_NORMAL);
		}

		if (keyManager->IsStayKeyDown('K'))
		{
			Fire(ATTACK_FALL);
		}

		if (keyManager->IsStayKeyDown('L') &&  (size.x * 1.8f) < pos.x )
		{
			Fire(ATTACK_SHARK);
		}

		if (keyManager->IsStayKeyDown('W'))
		{
			position.y = -1;
			CurUpDownState = UPDOWN_UP;
		}

		else if (keyManager->IsStayKeyDown('S'))
		{
			position.y = 1;
			CurUpDownState = UPDOWN_DOWN;
		}

		else
		{
			CurUpDownState = UPDOWN_NONE;
		}

		if (keyManager->IsStayKeyDown('A'))
		{
			position.x = -1;
		}

		else if (keyManager->IsStayKeyDown('D'))
		{
			position.x = 1;
		}

		const float size = sqrtf(position.x * position.x + position.y * position.y);

		if (size)
		{
			position.x /= size;
			position.y /= size;

			if (PLAYER_IDLE == CurState)
			{
				CurState = PLAYER_MOVE;
			}
		}

		pos.x += position.x * Speed * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += position.y * Speed * TimerManager::GetInstance()->GetDeltaTime();
	
		pos.x = ClampValue<float>(pos.x, 0.f + (this->size.x * 0.5f), WINSIZE_X - (this->size.x * 0.5f));
		pos.y = ClampValue<float>(pos.y, 0.f + (this->size.y * 0.5f), WINSIZE_Y - (this->size.y * 0.5f));
	}
}

void Player::TakeDamage(int damage)
{
	if (PLAYER_ATTACK == CurState || PLAYER_DEAD == CurState)
	{
		return;
	}

	EffectManager::GetInstance()->AddEffectDefault("cuphead_plane_hit_fx_b", { pos.x , pos.y }, 0.3f);
	EffectManager::GetInstance()->AddEffectDefault("cuphead_plane_hit_fx", pos, 0.3f);
	AlphaTime = MaxAlphaTime;
	Hp = max(0, Hp - damage);

	if (0 >= Hp)
	{
		DeathUICoolTime = 3.f;
		CurState = PLAYER_DEAD;
		for (char pieceName = 'a'; pieceName <= 'e'; ++pieceName)
		{
			BrokenPiece* piece = new BrokenPiece((float)(uid(dre) % 2), (float)(uid(dre) % 4));
			piece->Init(pos, ("schmup_ch_piece_" + string{ pieceName }));
			ObjectManager::GetInstance()->AddObject(piece, OBJ_MONSTER);
		}
		for (char pieceName = 'a'; pieceName <= 'd'; ++pieceName)
		{
			BrokenPiece* piece = new BrokenPiece((float)(uid(dre) % 2), (float)(uid(dre) % 4));
			piece->Init(pos, ("schmup_gear_" + string{ pieceName }));
			ObjectManager::GetInstance()->AddObject(piece, OBJ_MONSTER);
		}
	}
}

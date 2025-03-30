#include "Sagittarius.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "SagittariusArrow.h"
#include "SagittariusStar.h"
#include "ObjectManager.h"

Sagittarius::Sagittarius()
	:Angle(0.f), AngleSpeed(0.f), CurrnetTime(0.f), AttackTime(0.f), bAttack(false)
{
}

void Sagittarius::Init(FPOINT InPos)
{
	State = ESagittariusState::Idle;
	pos = InPos;
	Speed = 150.f;
	FrameSpeed = 10.f;
	AngleSpeed = 250.f;
	AttackTime = 5.f;

	image = ImageManager::GetInstance()->AddImage("sagg_idle", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Idle/sagg_idle.bmp", 5580, 362, 12, 1, true, RGB(255, 0, 255));
}


void Sagittarius::Update()
{
	switch (State)
	{
	case Sagittarius::ESagittariusState::Idle:
		Idle();
		break;
	case Sagittarius::ESagittariusState::Attack:
		Attack();
		break;
	case Sagittarius::ESagittariusState::End:
		break;
	default:
		break;
	}

	UpdateFrame();

	Move();
}

void Sagittarius::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);
}

void Sagittarius::Move()
{
	Angle += AngleSpeed * TimerManager::GetInstance()->GetDeltaTime();

	pos.x += Speed * cosf(DEG_TO_RAD(Angle)) * TimerManager::GetInstance()->GetDeltaTime();
	pos.y -= Speed * sinf(DEG_TO_RAD(Angle * 0.5f)) * TimerManager::GetInstance()->GetDeltaTime();
}

void Sagittarius::TakeDamage(int damage)
{
}

void Sagittarius::Idle()
{
	CurrnetTime += TimerManager::GetInstance()->GetDeltaTime();
	if (CurrnetTime >= AttackTime)
	{
		FrameTime = 0.f;
		CurFrameIndex = 0;
		IsStayMaxFrame = true;

		CurrnetTime = 0.f;
		State = ESagittariusState::Attack;

		image = ImageManager::GetInstance()->AddImage("sagg_attack", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Attack/sagg_attack.bmp", 6496, 344, 14, 1, true, RGB(255, 0, 255));
	}
}

void Sagittarius::Attack()
{
	if (!bAttack && CurFrameIndex >= 6)
	{
		bAttack = true;
		
		FPOINT newPos = { pos.x, pos.y - 40.f };
		SagittariusStar* star = new SagittariusStar(newPos, 10.f, 180.f);
		star->Init();
		ObjectManager::GetInstance()->AddObject(star, OBJTYPE::OBJ_MONSTER_WEAPON);

		SagittariusStar* star1 = new SagittariusStar(newPos, 10.f, 125.f);
		star1->Init();
		ObjectManager::GetInstance()->AddObject(star1, OBJTYPE::OBJ_MONSTER_WEAPON);

		SagittariusStar* star2 = new SagittariusStar(newPos, 10.f, 225.f);
		star2->Init();
		ObjectManager::GetInstance()->AddObject(star2, OBJTYPE::OBJ_MONSTER_WEAPON);

		SagittariusArrow* arrow = new SagittariusArrow(newPos, { 50.f,50.f });
		arrow->Init();
		ObjectManager::GetInstance()->AddObject(arrow, OBJTYPE::OBJ_MONSTER_WEAPON);
	}
	else if (bAttack && CurFrameIndex == image->GetMaxFrameX() - 1)
	{
		FrameTime = 0.f;
		CurFrameIndex = 0;
		IsStayMaxFrame = false;

		bAttack = false;
		State = ESagittariusState::Idle;
		
		image = ImageManager::GetInstance()->AddImage("sagg_idle", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Idle/sagg_idle.bmp", 5580, 362, 12, 1, true, RGB(255, 0, 255));
	}
}

void Sagittarius::Release()
{
}
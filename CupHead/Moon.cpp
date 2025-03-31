#include "Moon.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "UFO.h"
#include "ObjectManager.h"
#include "EffectManager.h"

Moon::Moon()
	:State(EMoonState::End), CurrentTime(0.f), AttackTime(0.f), CurrentAttackCount(0), AttackCount(0), UFOSpawnTime(0.f), DeadEffectTime(0.f)
{
}

void Moon::Init()
{
	FrameSpeed = 25.f;
	Hp = 5;

	AttackTime = 5.f;
	UFOSpawnTime = 2.f;
	DeadEffectTime = 0.5f;

	State = EMoonState::Idle;
	image = ImageManager::GetInstance()->AddImage("blimp_moon_idle", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_idle.bmp", 13120, 773, 16, 1, true, RGB(255, 0, 255));

	ColliderComponent = new Collider(this,COLLIDERTYPE::Rect,{ (float)image->GetFrameWidth() * 0.2f,0.f},{(float)image->GetFrameWidth() * 0.25f,(float)image->GetFrameHeight() * 0.5f},true,1.f);
	ColliderComponent->Init();
	CollisionManager::GetInstance()->AddCollider(ColliderComponent, OBJ_MONSTER);

	pos.x = WINSIZE_X - image->GetFrameWidth() * 0.4f;
	pos.y = WINSIZE_Y * 0.5f;

	EffectInit();
}

void Moon::Update()
{
	UpdateFrame();

	CurrentTime += TimerManager::GetInstance()->GetDeltaTime();
	switch (State)
	{
	case Moon::EMoonState::Idle:
		Idle();
		break;
	case Moon::EMoonState::Attack:
		Attack();
		break;
	case Moon::EMoonState::Dead:
		Dead();
		break;
	case Moon::EMoonState::End:
		break;
	default:
		break;
	}
}

void Moon::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);
}


void Moon::TakeDamage(int damage)
{
	if (Hp <= 0)
		return;

	Hp -= damage;

	if (Hp <= 0)
	{
		CurFrameIndex = 0;
		FrameTime = 0.f;
		IsStayMaxFrame = false;

		State = EMoonState::Dead;
		image = ImageManager::GetInstance()->AddImage("blimp_moon_death", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_death.bmp", 10144, 810, 16, 1, true, RGB(255, 0, 255));

		ColliderComponent->SetDead(true);
	}		
}

void Moon::Idle()
{
	if (CurrentTime >= AttackTime)
	{
		CurFrameIndex = 0;
		FrameTime = 0.f;
		IsStayMaxFrame = true;

		CurrentTime = UFOSpawnTime;
		State = EMoonState::Attack;

		image = ImageManager::GetInstance()->AddImage("blimp_moon_attack", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_attack.bmp", 23582, 808, 26, 1, true, RGB(255, 0, 255));

		CurrentAttackCount = 0;
		AttackCount = uid(dre) % 35 + 15;		// 어택 싸이클 횟수 15 ~ 50;
	}
}

void Moon::Attack()
{
	if (CurrentTime >= UFOSpawnTime)
	{
		CurrentTime = 0.f;

		UFOSpawn();
	}

	//  공격프레임이 12 ~ 19
	if (CurrentAttackCount <= AttackCount && CurFrameIndex > 19)
	{
		CurFrameIndex = 12;
		FrameTime = 12.f;

		++CurrentAttackCount;
		ColliderComponent->SetPivot({ -(float)image->GetFrameWidth() * 0.1f,0.f });
	}
	else if (CurFrameIndex == image->GetMaxFrameX() - 1)
	{
		CurFrameIndex = 0;
		FrameTime = 0.f;
		IsStayMaxFrame = false;

		CurrentTime = 0.f;
		State = EMoonState::Idle;

		image = ImageManager::GetInstance()->AddImage("blimp_msoon_idle", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_idle.bmp", 13120, 773, 16, 1, true, RGB(255, 0, 255));

		ColliderComponent->SetPivot({ (float)image->GetFrameWidth() * 0.2f, 0.f });		
	}	
	else if (CurFrameIndex < 12 && CurFrameIndex >= 9)
		ColliderComponent->SetPivot({ (float)image->GetFrameWidth() * (0.2f - (CurFrameIndex / 9 * 0.3f)),0.f });
	else if(CurFrameIndex < image->GetMaxFrameX() && CurFrameIndex > 19)
		ColliderComponent->SetPivot({ (float)image->GetFrameWidth() * (0.2f - (CurFrameIndex / (image->GetMaxFrameX() - 1) * 0.3f)),0.f });

	if (CurFrameIndex == 9 || CurFrameIndex == 23)
		EffectManager::GetInstance()->AddEffect("blimp_moon_smoke", pos, 1.f,{ (float)image->GetFrameWidth() * 0.2f,0.f});
}

void Moon::Dead()
{
	if (CurrentTime >= DeadEffectTime)
	{
		// 귀차니즘으로 인해 그냥 함.
		uniform_int_distribution<int> randX{ int(pos.x - image->GetFrameWidth() * 0.5f), int(pos.x + image->GetFrameWidth() * 0.5f) };
		uniform_int_distribution<int> randY{ int(pos.y - image->GetFrameHeight() * 0.25f), int(pos.y + image->GetFrameHeight() * 0.25f) };

		const int x = randX(dre);
		const int y = randY(dre);

		CurrentTime = 0.f;
		EffectManager::GetInstance()->AddEffect("boss_explosion", { (float)x,(float)y }, 1.f);
	}
}

void Moon::UFOSpawn()
{
	UFO* ufo = new UFO();
	ufo->Init({ WINSIZE_X,WINSIZE_Y * 0.5f});
	ObjectManager::GetInstance()->AddObject(ufo, OBJTYPE::OBJ_MONSTER);
}

void Moon::EffectInit()
{
	ImageManager::GetInstance()->AddImage("blimp_moon_smoke", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_smoke.bmp", 9315, 752, 15, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("boss_explosion", L"Image/CupHead/Hilda Berg/Moon/boss_explosion.bmp", 7480, 728, 11, 1, true, RGB(255, 0, 255));
}

void Moon::Release()
{
}
#include "Moon.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"

Moon::Moon()
	:State(EMoonState::End), CurrentAttackTime(0.f), AttackTime(0.f),CurrentAttackCount(0),AttackCount(0), CurrentUFOTime(0.f), UFOSpawnTime(0.f)
{
}

void Moon::Init()
{
	FrameSpeed = 25.f;

	AttackTime = 5.f;

	State = EMoonState::Idle;
	image = ImageManager::GetInstance()->AddImage("blimp_moon_idle", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_idle.bmp", 13120, 773, 16, 1, true, RGB(255, 0, 255));

	ColliderComponent = new Collider(this,COLLIDERTYPE::Rect,{ (float)image->GetFrameWidth() * 0.2f,0.f},{(float)image->GetFrameWidth() * 0.25f,(float)image->GetFrameHeight() * 0.5f},true,1.f);
	ColliderComponent->Init();
	CollisionManager::GetInstance()->AddCollider(ColliderComponent, OBJ_MONSTER);

	pos.x = WINSIZE_X - image->GetFrameWidth() * 0.4f;
	pos.y = WINSIZE_Y * 0.5f;
}

void Moon::Update()
{
	UpdateFrame();

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

	CurrentUFOTime += TimerManager::GetInstance()->GetDeltaTime();
	if (CurrentUFOTime >= UFOSpawnTime)
	{
		CurrentUFOTime = 0.f;
		UFOSpawnTime = uid(dre);
	}
}

void Moon::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);
}


void Moon::TakeDamage(int damage)
{
}

void Moon::Idle()
{
	CurrentAttackTime += TimerManager::GetInstance()->GetDeltaTime();

	if (CurrentAttackTime >= AttackTime)
	{
		CurFrameIndex = 0;
		FrameTime = 0.f;
		IsStayMaxFrame = true;

		CurrentAttackTime = 0.f;
		State = EMoonState::Attack;

		image = ImageManager::GetInstance()->AddImage("blimp_moon_attack", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_attack.bmp", 23582, 808, 26, 1, true, RGB(255, 0, 255));

		CurrentAttackCount = 0;
		AttackCount = uid(dre) % 5 + 5;		
	}
}

void Moon::Attack()
{
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

		State = EMoonState::Idle;

		image = ImageManager::GetInstance()->AddImage("blimp_msoon_idle", L"Image/CupHead/Hilda Berg/Moon/blimp_moon_idle.bmp", 13120, 773, 16, 1, true, RGB(255, 0, 255));

		ColliderComponent->SetPivot({ (float)image->GetFrameWidth() * 0.2f, 0.f });		
	}	
	else if (CurFrameIndex < 12 && CurFrameIndex >= 9)
		ColliderComponent->SetPivot({ (float)image->GetFrameWidth() * (0.2f - (CurFrameIndex / 9 * 0.3f)),0.f });
	else if(CurFrameIndex < image->GetMaxFrameX() && CurFrameIndex > 19)
		ColliderComponent->SetPivot({ (float)image->GetFrameWidth() * (0.2f - (CurFrameIndex / (image->GetMaxFrameX() - 1) * 0.3f)),0.f });
}

void Moon::Dead()
{
}

void Moon::UFOSpawn()
{
}

void Moon::Release()
{
}
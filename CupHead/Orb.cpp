#include "Orb.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include <random>

Orb::Orb(FPOINT InPos, float InSize)
	:StateChangeTime(0.f), AttackPosition({0.f,0.f}), Dir(DIRECTION_LEFT), bFlip(false)
{
	pos = InPos;
	size.x = InSize;
	size.y = InSize;
}

void Orb::Init()
{
	image = ImageManager::GetInstance()->AddImage("orb_loop", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_loop.bmp", 2272, 143, 16, 1, true, RGB(255, 0, 255));
	State = OrbState::Idle;

	OrbCollider = new Collider(this, COLLIDERTYPE::Sphere, { 2272 / 16 * 0.5f,0.f }, 30.f, true);
	OrbCollider->Init();
	CollisionManager::GetInstance()->AddCollider(OrbCollider,OBJ_MONSTER);

	Speed = 1000.f;	
	FrameSpeed = 10.f;

	InitRandom();
}

void Orb::Release()
{
}

void Orb::Update()
{
	UpdateFrame();

	Move();
}

void Orb::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y - (image->GetHeight() * 0.5f), CurFrameIndex, bFlip);
}

void Orb::Move()
{
	switch (State)
	{
	case OrbState::Idle:
		Idle();
		break;
	case OrbState::MoveUp:
		MoveUp();
		break;
	case OrbState::MoveDown:
		MoveDown();
		break;
	case OrbState::Attack:
		Attack();
		break;
	case OrbState::Dead:
		Dead();
		break;
	case OrbState::End:
		break;
	default:
		break;
	}
}

void Orb::Idle()
{
	StateChangeTime += TimerManager::GetInstance()->GetDeltaTime();

	if (StateChangeTime >= 1.f)
	{
		StateChangeTime = 0.f;
		State = OrbState::MoveUp;

		image = ImageManager::GetInstance()->AddImage("orb_leave", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_leave.bmp", 2145, 505, 15, 1, true, RGB(255, 0, 255));
		
		ResetFrame();

		IsStayMaxFrame = true;
	}
}

void Orb::MoveUp()
{
	if (CurFrameIndex == image->GetMaxFrameX() - 1)
	{
		State = OrbState::MoveDown;
		image = ImageManager::GetInstance()->AddImage("orb_attack_intro", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_attack_intro.bmp", 973, 193, 7, 1, true, RGB(255, 0, 255));

		pos.x = AttackPosition.x;
		pos.y = 0.f;

		ResetFrame();

		IsStayMaxFrame = true;
	}
}

void Orb::MoveDown()
{
	if (pos.y >= AttackPosition.y && CurFrameIndex == image->GetMaxFrameX() - 1)
	{
		State = OrbState::Attack;

		image = ImageManager::GetInstance()->AddImage("orb_attack_loop", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_attack_loop.bmp", 552, 139, 4, 1, true, RGB(255, 0, 255));

		ResetFrame();

		bFlip = (bool)Dir;
	}
	else if(pos.y < AttackPosition.y)
		pos.y += Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void Orb::Attack()
{
}

void Orb::Dead()
{
}

void Orb::InitRandom()
{
	RandomAttackPosition();
	RandomDir();
}

void Orb::RandomAttackPosition()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> randX(200, 400);
	uniform_int_distribution<int> randY(100, 300);

	AttackPosition.x = (float)randX(mt);
	AttackPosition.y = (float)randY(mt);
}

void Orb::RandomDir()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dir(0, 1);

	Dir = (DIRECTION)dir(mt);
}

void Orb::ResetFrame()
{
	CurFrameIndex = 0;
	FrameTime = 0.f;
	IsStayMaxFrame = false;
}

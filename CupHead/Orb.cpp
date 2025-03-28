#include "Orb.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"

Orb::Orb(FPOINT InPos, FPOINT InSize)
{
	pos = InPos;
	size = InSize;
}

void Orb::Init()
{
	image = ImageManager::GetInstance()->AddImage("orb_loop", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_loop.bmp", 2272, 143, 16, 1, true, RGB(255, 0, 255));
	State = OrbState::Idle;

	Collider* collider = new Collider(this, COLLIDERTYPE::Sphere, { 2272 / 16 * 0.5f,143 * 0.5f }, 30.f, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider,OBJ_MONSTER);

	Speed = 200.f;	
}

void Orb::Release()
{
}

void Orb::Update()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	StateChangeTime += TimerManager::GetInstance()->GetDeltaTime();

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		if (true == IsStayMaxFrame)
			CurFrameIndex = image->GetMaxFrameX() - 1;
		else
			CurFrameIndex = FrameTime = 0.f;
	}

	Move();
}

void Orb::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y, CurFrameIndex);
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
	if (StateChangeTime >= 0.5f)
	{
		StateChangeTime = 0.f;
		State = OrbState::MoveUp;

		image = ImageManager::GetInstance()->AddImage("orb_leave", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_leave.bmp", 2145, 505, 15, 1, true, RGB(255, 0, 255));
		CurFrameIndex = 0;
	}
}

void Orb::MoveUp()
{
	if (pos.y - image->GetHeight() <= 0.f)
	{
		State = OrbState::MoveDown;

		image = ImageManager::GetInstance()->AddImage("orb_attack_intro", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_attack_intro.bmp", 973, 193, 7, 1, true, RGB(255, 0, 255));
		CurFrameIndex = 0;
	}
	else
		pos.y -= Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void Orb::MoveDown()
{
}

void Orb::Attack()
{
}

void Orb::Dead()
{
}

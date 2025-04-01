#include "PlayerSharkMissile.h"
#include "Image.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"

PlayerSharkMissile::PlayerSharkMissile() : IsLoop(true)
{
	Speed = 900.f;
	FrameSpeed = 15.f;
	//IsStayMaxFrame = true;
	this->size = { 100.f, 80.f };
	image = ImageManager::GetInstance()->AddImage("SharkMissile", TEXT("Image/CupHead/cuphead_plane/Shoot/SharkMissile.bmp"), 4816, 109, 28, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, size, true, 0.2f); // 임의값 0.2f
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER_WEAPON);
	EffectManager::GetInstance()->AddEffect("SharkStartFire", pos, 3 / FrameSpeed, { -90.f, 0.f }, 1, true, this);
}

PlayerSharkMissile::~PlayerSharkMissile()
{
}

void PlayerSharkMissile::Init(FPOINT _Pos, int _Damage)
{
	__super::Init(_Pos, _Damage);
}

void PlayerSharkMissile::Init()
{
}

void PlayerSharkMissile::Release()
{
}

void PlayerSharkMissile::Update()
{
	UpdateFrame();
	Move();
}

void PlayerSharkMissile::Render(HDC hdc)
{
	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
}

void PlayerSharkMissile::UpdateFrame()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	if (true == IsLoop && 3 == CurFrameIndex)
	{
		EffectManager::GetInstance()->AddEffect("SharkLoopFire", pos, 5.f, { -90.f, 0.f }, 20.f, true, this);
		IsLoop = false;
	}

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		if (true == IsStayMaxFrame)
		{
			CurFrameIndex = image->GetMaxFrameX() - 1;
		}

		else
		{
			CurFrameIndex = FrameTime = 0.f;
		}
	}
}

void PlayerSharkMissile::Move()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	pos.x += (Speed * DeltaTime);

	if (OutOfScreen(FPOINT{ pos.x - size.x / 2, pos.y }, image->GetFrameWidth(), image->GetFrameHeight())) // 이펙트 때문에 부자연스러워서 위치 조정
	{
		bDead = true;
	}
}

void PlayerSharkMissile::TakeDamage(int damage)
{
	EffectManager::GetInstance()->AddEffectDefault("LargeSpark", { (pos.x + size.x / 2), pos.y }, 0.2f);
}

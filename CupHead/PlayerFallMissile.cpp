#include "PlayerFallMissile.h"
#include "Image.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"

PlayerFallMissile::PlayerFallMissile() : MoveTime(0.f), Gravity(25.8f)
{
	Speed = 1000.f;
	FrameSpeed = 20.f;
	//IsStayMaxFrame = true;
	int MaxAnimationFrame = 9;
	// D:\Programming\Git\CupHead\CupHead\Image\CupHead\cuphead_plane\Shoot
	image = ImageManager::GetInstance()->AddImage("FallMissile", TEXT("Image/CupHead/cuphead_plane/Shoot/FallMissile.bmp"), 406, 41, 7, 1, true, RGB(255, 0, 255));
	//image = ImageManager::GetInstance()->AddImage("SharkMissile", TEXT("Image/CupHead/cuphead_plane/Shoot/SharkMissile.bmp"), 4816, 109, 28, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { 90.f, 30.f }, false);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER_WEAPON);
}

PlayerFallMissile::~PlayerFallMissile()
{

}

void PlayerFallMissile::Init(FPOINT _Pos, int _Damage)
{
	__super::Init(_Pos, _Damage);
	InitPos = pos = _Pos;
}

void PlayerFallMissile::Init()
{
}

void PlayerFallMissile::Release()
{
}

void PlayerFallMissile::Update()
{
	UpdateFrame();
	Move();
}

void PlayerFallMissile::Render(HDC hdc)
{
	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
}

void PlayerFallMissile::Move()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	MoveTime += 10.f * DeltaTime;
	pos.x += Speed * DeltaTime;
	pos.y = InitPos.y + Gravity * 0.5f * pow(MoveTime, 2);

	if (OutOfScreen(FPOINT{ pos.x + image->GetFrameWidth() * 0.5f, pos.y }, image->GetFrameWidth(), image->GetFrameHeight()))
	{
		bDead = true;
	}
}

void PlayerFallMissile::TakeDamage(int damage)
{
	__super::TakeDamage(damage);
	EffectManager::GetInstance()->AddEffectDefault("LargeExplosion", pos, 0.3f);
	EffectManager::GetInstance()->AddEffectDefault("LargeFire", pos, 0.3f);
	bDead = true;
}

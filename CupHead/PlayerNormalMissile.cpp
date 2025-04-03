#include "PlayerNormalMissile.h"
#include "Image.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"

PlayerNormalMissile::PlayerNormalMissile()
{
	Speed = 1500.f;
	FrameSpeed = 15.f;
	//IsStayMaxFrame = true;
	int MaxAnimationFrame = 9;
	// D:\Programming\Git\CupHead\CupHead\Image\CupHead\cuphead_plane\Shoot
	image = ImageManager::GetInstance()->AddImage("schmup_peashot_bullet", TEXT("Image/CupHead/cuphead_plane/Shoot/schmup_peashot_bullet.bmp"), 909, 19, MaxAnimationFrame, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { 90.f, 30.f }, false);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER_WEAPON);
}

PlayerNormalMissile::~PlayerNormalMissile()
{
}

void PlayerNormalMissile::Init(FPOINT _Pos, int _Damage)
{
	__super::Init(_Pos, _Damage);
}

void PlayerNormalMissile::Init()
{
}

void PlayerNormalMissile::Release()
{
}

void PlayerNormalMissile::Update()
{
	UpdateFrame();
	Move();
}

void PlayerNormalMissile::Render(HDC hdc)
{
	__super::Render(hdc);
}

void PlayerNormalMissile::Move()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	pos.x += (Speed * DeltaTime);

	if (OutOfScreen(FPOINT{ pos.x + image->GetFrameWidth() * 0.5f, pos.y }, image->GetFrameWidth(), image->GetFrameHeight()))
	{
		bDead = true;
	}
}

void PlayerNormalMissile::TakeDamage(int damage)
{
	__super::TakeDamage(damage);
	EffectManager::GetInstance()->AddEffectDefault("schmup_peashot_hit_spark", pos, 0.3f);
	bDead = true;
}

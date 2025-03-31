#include "PlayerMissile.h"
#include "Image.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"

PlayerMissile::PlayerMissile() : LookAngle(DEG_TO_RAD(0.f))
{
	Speed = 1500.f;
	FrameSpeed = 15.f;
	//IsStayMaxFrame = true;
	int MaxAnimationFrame = 9;
	// D:\Programming\Git\CupHead\CupHead\Image\CupHead\cuphead_plane\Shoot
	image = ImageManager::GetInstance()->AddImage("schmup_peashot_bullet", TEXT("Image/CupHead/cuphead_plane/Shoot/schmup_peashot_bullet.bmp"), 909, 19, MaxAnimationFrame, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { 165.f, 70.f }, false);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER_WEAPON);
}

PlayerMissile::~PlayerMissile()
{
}

void PlayerMissile::Init(FPOINT _Pos)
{
	pos = _Pos;
}

void PlayerMissile::Init()
{
}

void PlayerMissile::Release()
{
}

void PlayerMissile::Update()
{
	UpdateFrame();
	Move();
}

void PlayerMissile::Render(HDC hdc)
{
	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
}

void PlayerMissile::Move()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	pos.x += (Speed * DeltaTime);

	if (OutOfScreen(FPOINT{ pos.x + image->GetFrameWidth() * 0.5f, pos.y }, image->GetFrameWidth(), image->GetFrameHeight()))
	{
		bDead = true;
	}
}

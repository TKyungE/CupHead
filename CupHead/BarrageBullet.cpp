#include "BarrageBullet.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EffectManager.h"

BarrageBullet::BarrageBullet()
	: Angle{}, DeltaAngle{},
	ElapsedTime{}, Life{}
{
}

BarrageBullet::~BarrageBullet()
{
}

void BarrageBullet::Init(FPOINT _Pos, float _Angle, float _DeltaAngle, float _Life)
{
#pragma region Image Load
	// star ÀÌ¹ÌÁö
	image = ImageManager::GetInstance()->AddImage("BarrageBullet", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_a.bmp"), 1632, 108, 16, 1, true, RGB(255, 0, 255));
#pragma endregion

	pos = _Pos;
	Angle = _Angle;
	DeltaAngle = _DeltaAngle;
	Life = _Life;

	CurFrameIndex = 0;
	FrameSpeed = 10.f;
	FrameTime = 0.f;

	Speed = 500.f;
	IsFlip = false;
	size = { 1.f,1.f };
	bDead = false;

	float sizeX = 0.f;
	float sizeY = 0.f;
	if (image)
	{
		sizeX = image->GetFrameWidth();
		sizeY = image->GetFrameHeight();
	}
	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { sizeX * 0.5f, sizeY * 0.5f }, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER_WEAPON);
}

void BarrageBullet::Release()
{
}

void BarrageBullet::Update()
{
	UpdateFrame();
	UpdateAngle();
	Move();

	ElapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (ElapsedTime > Life)
	{
		bDead = true;
	}
}

void BarrageBullet::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, false);
}

void BarrageBullet::Move()
{
	pos.x += Speed * TimerManager::GetInstance()->GetDeltaTime()
		* cosf((float)DEG_TO_RAD(Angle));
	pos.y -= Speed * TimerManager::GetInstance()->GetDeltaTime()
		* sinf((float)DEG_TO_RAD(Angle));
}

void BarrageBullet::TakeDamage(int damage)
{
	Hp -= damage;
	if (Hp <= 0)
	{
		bDead = true;
	}
}

void BarrageBullet::UpdateAngle()
{
	Angle += DeltaAngle * TimerManager::GetInstance()->GetDeltaTime();
	DeltaAngle -= 20.f * TimerManager::GetInstance()->GetDeltaTime();
	DeltaAngle = ClampValue(DeltaAngle, 0.f, DeltaAngle);
}

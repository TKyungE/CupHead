#include "LaughProjectile.h"
#include "Image.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"

LaughProjectile::LaughProjectile() : LookAngle(0.f), MoveValue(0.f)
{
	Speed = 300.f;
	LookAngle = DEG_TO_RAD(180.f);
	FrameSpeed = 15.f;
	SinValue = 0.1f;
	IsStayMaxFrame = true;
	int MaxAnimationFrame = 13;
	image = ImageManager::GetInstance()->AddImage("blimp_ha", TEXT("Image/CupHead/Hilda Berg/Normal/Attack/blimp_ha.bmp"), 2262, 74, MaxAnimationFrame, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { 165.f, 70.f }, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER_WEAPON);
}

LaughProjectile::~LaughProjectile()
{

}

void LaughProjectile::Init(FPOINT _Pos)
{
	pos = _Pos;
	//EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 30.f, { 100.f, 0.f }, 30, true, this); // Trace는 되는데 생각해보니 버그 생길듯 수정 필요.
}

void LaughProjectile::Init()
{
	//EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 30.f, { 100.f, 0.f }, 30, true, this); // Trace는 되는데 생각해보니 버그 생길듯 수정 필요.
}

void LaughProjectile::Release()
{

}

void LaughProjectile::Update()
{
	UpdateFrame();
	Move();
}

void LaughProjectile::Render(HDC hdc)
{
	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
}

void LaughProjectile::Move()
{
	// 매직 넘버는 일단 애니메이션 보면서 느낌 맞추기

	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	MoveValue += DeltaTime;
	SinValue += DeltaTime * 0.15f;
	Speed += DeltaTime * 1800.f;

	SinValue = min(0.3f, SinValue);
	Speed = min(2000.f, Speed);

	float BaseDirX = cosf(LookAngle);
	float BaseDirY = -sinf(LookAngle);
	float PerDirX = -BaseDirY;
	float PerDirY = BaseDirX;

	float WaveOffset = SinValue * sinf(15.f * MoveValue);
	//float waveOffset = cosf(float(MoveValue));

	pos.x += (Speed * DeltaTime) * BaseDirX + PerDirX * WaveOffset;
	pos.y += (Speed * DeltaTime) * BaseDirY + PerDirY * WaveOffset;

	if (OutOfScreen(FPOINT{ pos.x + image->GetFrameWidth() * 0.5f, pos.y }, image->GetFrameWidth(), image->GetFrameHeight()))
	{
		bDead = true;
	}
}

#include "LaughProjectile.h"
#include "Image.h"
#include "ImageManager.h"

LaughProjectile::LaughProjectile() : LookAngle(0.f), MoveValue(0.f)
{
	Speed = 300.f;
	pos = { 1000,300 };
	LookAngle = DEG_TO_RAD(180.f);
	FrameSpeed = 15.f;
	SinValue = 0.005f;
	IsStayMaxFrame = true;
	int MaxAnimationFrame = 13;
	image = ImageManager::GetInstance()->AddImage("blimp_ha", TEXT("Image/CupHead/Hilda Berg/Normal/Attack/blimp_ha.bmp"), 2262, 74, MaxAnimationFrame, 1, true, RGB(255, 0, 255));
}

LaughProjectile::~LaughProjectile()
{

}

void LaughProjectile::Init()
{

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
	SinValue += DeltaTime * 0.05f;
	Speed += DeltaTime * 350.f;

	SinValue = min(0.07f, SinValue);
	Speed = min(500.f, Speed);

	float BaseDirX = cosf(LookAngle);
	float BaseDirY = -sinf(LookAngle);
	float PerDirX = -BaseDirY;
	float PerDirY = BaseDirX;

	float WaveOffset = SinValue * sinf(10.f * MoveValue);
	//float waveOffset = cosf(float(MoveValue));

	pos.x += (Speed * DeltaTime) * BaseDirX + PerDirX * WaveOffset;
	pos.y += (Speed * DeltaTime) * BaseDirY + PerDirY * WaveOffset;
}

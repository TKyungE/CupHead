#include "StarProjectile.h"
#include "Image.h"
#include "ImageManager.h"

StarProjectile::StarProjectile() : LookAngle(180.f), MoveValue(0.f)
{
	pos = { 1000,300 };
	LookAngle = DEG_TO_RAD(180.f);

	Speed = 700.f;
	FrameSpeed = 10.f;
	SinValue = 0.11f;
	image = ImageManager::GetInstance()->AddImage("blimp_star_a", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_a.bmp"), 1632, 108, 16, 1, true, RGB(255, 0, 255));

	//Speed = 500.f;
	//FrameSpeed = 25.f;
	//SinValue = 0.13f;
	//image = ImageManager::GetInstance()->AddImage("blimp_star_b", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_b.bmp"), 819, 117, 7, 1, true, RGB(255, 0, 255));

	//Speed = 600.f;
	//FrameSpeed = 12.f;
	//SinValue = 0.15f;
	//image = ImageManager::GetInstance()->AddImage("blimp_star_c", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_c.bmp"), 1482, 113, 13, 1, true, RGB(255, 0, 255));

	// C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\Hilda Berg\Moon\Attack

}

StarProjectile::~StarProjectile()
{

}

void StarProjectile::Init()
{

}

void StarProjectile::Release()
{

}

void StarProjectile::Update()
{
	UpdateFrame();
	Move();
}

void StarProjectile::Render(HDC hdc)
{
	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
}

void StarProjectile::Move()
{

	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();

	MoveValue += DeltaTime;
	//SinValue += DeltaTime * 0.1f;
	//Speed += DeltaTime * 50.f;

	//SinValue = min(0.1f, SinValue);
	//Speed = min(1000.f, Speed);

	float BaseDirX = cosf(LookAngle);
	float BaseDirY = -sinf(LookAngle);
	float PerDirX = -BaseDirY;
	float PerDirY = BaseDirX;

	float WaveOffset = SinValue * sinf(5.f * MoveValue);
	//float waveOffset = cosf(float(MoveValue));

	//moveSpeed = 10.f;
	pos.x += (Speed * DeltaTime) * BaseDirX + PerDirX * WaveOffset;
	pos.y += (Speed * DeltaTime) * BaseDirY + PerDirY * WaveOffset;

	if (pos.x < 0) // Debug
	{
		pos.x = 1000;
	}
}

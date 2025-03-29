#include "UFOBeam.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"

UFOBeam::UFOBeam()
{
}

void UFOBeam::Init()
{
	FrameSpeed = 10.f;
	IsStayMaxFrame = true;
	image = ImageManager::GetInstance()->AddImage("blimp_moon_ufo_beam", L"Image/CupHead/Hilda Berg/Moon/Attack/blimp_moon_ufo_beam.bmp", 3768, 725, 24, 1, true, RGB(255, 0, 255));
}

void UFOBeam::Update(FPOINT parentPos)
{
	UpdateFrame();
	Attack();

	if (image != nullptr)
	{
		if (CurFrameIndex == image->GetMaxFrameX() - 1)
			bDead = true;
	}

	pos.x = parentPos.x;
	pos.y = parentPos.y;
}

void UFOBeam::Render(HDC hdc)
{
	if (image && !bDead)
		image->Render(hdc, pos.x, pos.y, CurFrameIndex);
}

void UFOBeam::Attack()
{
	if (CurFrameIndex > 8 && CurFrameIndex < 18)
	{
		FHitResult HitResult;
		bool bCheck = CollisionManager::GetInstance()->LineTraceByObject(HitResult, OBJTYPE::OBJ_PLAYER, {pos.x,pos.y}, {pos.x, WINSIZE_Y}, this, true, true, 0.01f, RGB(255, 0, 255));
		if (bCheck)		// ¸Â¾Ò´Ù.
			HitResult.HitObj->TakeDamage(1);
	}
}

void UFOBeam::Release()
{
}
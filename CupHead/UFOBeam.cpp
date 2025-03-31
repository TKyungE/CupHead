#include "UFOBeam.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"

UFOBeam::UFOBeam()
	:Owner(nullptr)
{
}

void UFOBeam::Init(GameObject* InOwner, FPOINT InPivot)
{ 
	Owner = InOwner;
	Pivot = InPivot;
	FrameSpeed = 10.f;
	IsStayMaxFrame = true;
	CurFrameIndex = 0;
	FrameTime = 0.f;
	image = ImageManager::GetInstance()->AddImage("blimp_moon_ufo_beam", L"Image/CupHead/Hilda Berg/Moon/Attack/blimp_moon_ufo_beam.bmp", 3768, 725, 24, 1, true, RGB(255, 0, 255));
}

void UFOBeam::Update()
{
	UpdateFrame();

	Attack();

	if (image != nullptr)
	{
		if (CurFrameIndex == image->GetMaxFrameX() - 1)
			bDead = true;
	}

	if (Owner != nullptr)
	{
		pos.x = Owner->GetPos().x + Pivot.x;
		pos.y = Owner->GetPos().y + (Pivot.y * 2) - (37.f * 2);
	}
}

void UFOBeam::Render(HDC hdc)
{
	if (image && !bDead)
		image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0);
}

void UFOBeam::Attack()
{
	if (CurFrameIndex > 8 && CurFrameIndex < 18)
	{
		FHitResult HitResult;
		bool bCheck = CollisionManager::GetInstance()->LineTraceByObject(HitResult, OBJTYPE::OBJ_PLAYER, { pos.x,Owner->GetPos().y }, { pos.x, WINSIZE_Y }, this, true, true, 0.01f, RGB(255, 0, 255));
		if (bCheck)		// ¸Â¾Ò´Ù.
			HitResult.HitObj->TakeDamage(1);
	}
}


void UFOBeam::Release()
{
}
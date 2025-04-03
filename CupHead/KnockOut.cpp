#include "KnockOut.h"
#include "Image.h"
#include "ImageManager.h"
#include "LevelManager.h"
#include "Fade.h"
#include "ObjectManager.h"

KnockOut::KnockOut()
{
}

void KnockOut::Init()
{
	pos.x = WINSIZE_X * 0.5f;
	pos.y = WINSIZE_Y * 0.5f;

	FrameSpeed = 10.f;
	IsStayMaxFrame = true;

	image = ImageManager::GetInstance()->AddImage("FightText_KO", L"Image/CupHead/UI/FightText_KO.bmp", 13824, 288,27,1, true, RGB(255, 0, 255));
	image->SetScale(2.f, 2.f);
}

void KnockOut::Update()
{
	__super::Update();

	if (CurFrameIndex == image->GetMaxFrameX() - 1)
	{
		Fade* fadeOut = new Fade();
		fadeOut->Init(EFadeMode::FadeOut, ELevelState::Result);
		ObjectManager::GetInstance()->AddObject(fadeOut, OBJ_UPPERUI);

		bDead = true;
	}		
}

void KnockOut::Render(HDC hdc)
{
	__super::Render(hdc);
}

void KnockOut::Release()
{
}

KnockOut::~KnockOut()
{
}
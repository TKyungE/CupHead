#include "KnockOut.h"
#include "Image.h"
#include "ImageManager.h"
#include "LevelManager.h"

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
		bDead = true;
		LevelManager::GetInstance()->SetNextLevelState(ELevelState::Result);
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
#include "Fade.h"
#include "Image.h"
#include "ImageManager.h"

Fade::Fade()
	:FadeMode(EFadeMode::End), FrameDir(1), Alpha(0.f)
{
}

void Fade::Init(EFadeMode InFadeMode)
{
	FrameSpeed = 15.f;
	
	image = ImageManager::GetInstance()->AddImage("Fade", L"Image/CupHead/UI/Screen/Fade/Fade.bmp", 8704, 288, 17, 1, true, RGB(255, 0, 255));
	image->SetScale(5.f, 5.f);
	SetFadeMode(InFadeMode);
}

void Fade::Update()
{
	UpdateFrame();
}

void Fade::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f, CurFrameIndex, CurFrameYIndex);
		//image->FrameRenderAlpha(hdc, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f, CurFrameIndex, CurFrameYIndex, false, Alpha);
}

void Fade::UpdateFrame()
{
	FrameTime += (FrameSpeed * TimerManager::GetInstance()->GetDeltaTime()) * FrameDir;
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		CurFrameIndex = image->GetMaxFrameX() - 1;
		bDead = true;
		//SetFadeMode(EFadeMode::FadeOut);
	}

	else if (FrameDir == -1 && CurFrameIndex < 0)
	{
		CurFrameIndex = 0;
		bDead = true;

		//SetFadeMode(EFadeMode::FadeIn);
	}
}

void Fade::SetFadeMode(EFadeMode InFadeMode)
{
	if (FadeMode == InFadeMode)
		return;

	FadeMode = InFadeMode;
	switch (FadeMode)
	{
	case EFadeMode::FadeIn:
		FrameDir = 1;
		FrameTime = 0.f;
		break;
	case EFadeMode::FadeOut:
		FrameDir = -1;
		FrameTime = image->GetMaxFrameX() - 1;
		break;
	}
}

void Fade::Release()
{
}

Fade::~Fade()
{
}
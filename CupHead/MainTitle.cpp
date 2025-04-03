#include "MainTitle.h"
#include "Image.h"
#include "ImageManager.h"

MainTitle::MainTitle()
	:BackGround(nullptr)
{
}

void MainTitle::Init()
{
	FrameSpeed = 30.f;
	BackGround = ImageManager::GetInstance()->FindImage("title_screen_background");
	image = ImageManager::GetInstance()->FindImage("cuphead_title_screen");
}

void MainTitle::Update()
{
	UpdateFrame();
}

void MainTitle::Render(HDC hdc)
{
	if (BackGround != nullptr)
		BackGround->FrameRender(hdc, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f, 0, 0);

	if (image != nullptr)
		image->FrameRender(hdc, WINSIZE_X * 0.5f, WINSIZE_Y - (image->GetFrameHeight() * 0.5f - 10.f), CurFrameIndex, CurFrameYIndex);
}

void MainTitle::Release()
{
}

MainTitle::~MainTitle()
{
}

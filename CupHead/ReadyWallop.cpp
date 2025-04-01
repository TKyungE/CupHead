#include "ReadyWallop.h"
#include "Image.h"
#include "ImageManager.h"

ReadyWallop::ReadyWallop()
{
}

void ReadyWallop::Init()
{
	FrameSpeed = 15.f;
	IsStayMaxFrame = true;

	image = ImageManager::GetInstance()->AddImage("FightText_GetReady", L"Image/CupHead/UI/FightText_GetReady.bmp", 25600, 288, 50, 1, true, RGB(255, 0, 255));

	image->SetScale(3.f, 3.f);
}

void ReadyWallop::Update()
{
	if (CurFrameIndex >= image->GetMaxFrameX() - 1)
		bDead = true;
	
	UpdateFrame();
}

void ReadyWallop::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f, CurFrameIndex, CurFrameYIndex);
}

void ReadyWallop::Release()
{
}

ReadyWallop::~ReadyWallop()
{
}
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

	image = ImageManager::GetInstance()->FindImage("FightText_GetReady");

	image->SetScale(2.5f, 2.5f);
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
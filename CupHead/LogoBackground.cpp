#include "LogoBackground.h"
#include "Image.h"
#include "ImageManager.h"

LogoBackground::LogoBackground()
{
}

void LogoBackground::Init()
{
	pos.x = WINSIZE_X * 0.5f;
	pos.y = WINSIZE_Y * 0.5f;
	
	image = ImageManager::GetInstance()->FindImage("logobackground");	
}

void LogoBackground::Update()
{
	
}

void LogoBackground::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
}

void LogoBackground::Release()
{
}

LogoBackground::~LogoBackground()
{
}

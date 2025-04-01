#include "StartBtn.h"
#include "Image.h"
#include "ImageManager.h"

StartBtn::StartBtn()
{
}

void StartBtn::Init()
{
	image = ImageManager::GetInstance()->FindImage("StartBtn");
}


void StartBtn::Update()
{
}

void StartBtn::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
}

void StartBtn::Release()
{
}

StartBtn::~StartBtn()
{
}
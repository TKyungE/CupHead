#include "SimpleUI.h"
#include "Image.h"
#include "ImageManager.h"

SimpleUI::SimpleUI()
	:bRepeat(false), FrameDir(0)
{
}

void SimpleUI::Init(string InKey, float FrameSpeed, float InX, float InY, bool InRepeat)
{
	this->FrameSpeed = FrameSpeed;
	pos.x = InX;
	pos.y = InY;
	bRepeat = InRepeat;
	FrameDir = 1;
	image = ImageManager::GetInstance()->FindImage(InKey);
}

void SimpleUI::Update()
{
	UpdateFrame();
}

void SimpleUI::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, CurFrameYIndex);
}

void SimpleUI::UpdateFrame()
{
	FrameTime += (FrameSpeed * TimerManager::GetInstance()->GetDeltaTime()) * FrameDir;
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		if (bRepeat)
		{
			FrameDir = -1;
			CurFrameIndex = FrameTime = image->GetMaxFrameX() - 1;
		}
		else
			CurFrameIndex = FrameTime = 0.f;

	}
	else if(bRepeat && CurFrameIndex < 0)
	{
		CurFrameIndex = FrameTime = 0.f;
		FrameDir = 1;
	}

}

void SimpleUI::Release()
{
}

SimpleUI::~SimpleUI()
{
}
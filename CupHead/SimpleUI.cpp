#include "SimpleUI.h"
#include "Image.h"
#include "ImageManager.h"

SimpleUI::SimpleUI()
	:bRepeat(false), bPingPong(false),FrameDir(0), LifeCount(0),CurrentLifeCount(0)
{
}

void SimpleUI::Init(string InKey, float FrameSpeed, float InX, float InY, int InLifeCount, bool InPingPong, bool InRepeat)
{
	this->FrameSpeed = FrameSpeed;
	pos.x = InX;
	pos.y = InY;
	bRepeat = InRepeat;
	bPingPong = InPingPong;
	LifeCount = InLifeCount;

	FrameDir = 1;
	image = ImageManager::GetInstance()->FindImage(InKey);
}

void SimpleUI::Update()
{
	UpdateFrame();

	if (LifeCount > -1 && CurrentLifeCount >= LifeCount)
	{
		bDead = true;
	}
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
		if (!bRepeat)
			CurFrameIndex = FrameTime = image->GetMaxFrameX() - 1;
		else if (bPingPong)
		{
			FrameDir = -1;
			CurFrameIndex = FrameTime = image->GetMaxFrameX() - 1;
		}
		else
			CurFrameIndex = FrameTime = 0.f;

		++CurrentLifeCount;
	}
	else if (bPingPong && CurFrameIndex < 0)
	{
		CurFrameIndex = FrameTime = 0.f;
		FrameDir = 1;
		++CurrentLifeCount;
	}
}

void SimpleUI::Release()
{
}

SimpleUI::~SimpleUI()
{
}
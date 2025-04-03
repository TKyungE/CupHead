#include "Actor.h"
#include "Image.h"

Actor::Actor() : image(nullptr), CurFrameIndex(0), CurFrameYIndex(0), FrameSpeed(1.f), FrameTime(0.f), IsFlip(false), IsStayMaxFrame(false)
{
}

Actor::~Actor()
{
}

void Actor::Init()
{
}

void Actor::Release()
{
}

void Actor::Update()
{
	UpdateFrame();
}

void Actor::Render(HDC hdc)
{
}

void Actor::UpdateFrame()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		if (true == IsStayMaxFrame)
		{
			CurFrameIndex = image->GetMaxFrameX() - 1;
		}

		else
		{
			CurFrameIndex = FrameTime = 0.f;
		}
	}
}

void Actor::TakeDamage(int damage)
{
}

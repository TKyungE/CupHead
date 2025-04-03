#include "AlphaBackground.h"
#include "Image.h"
#include "ImageManager.h"
#include "LevelManager.h"

AlphaBackground::AlphaBackground()
	: Alpha(0.f)
{
}

void AlphaBackground::Init(float InAlphaSpeed)
{
	pos.x = WINSIZE_X * 0.5f;
	pos.y = WINSIZE_Y * 0.5f;

	Alpha = 255;
	AlphaSpeed = InAlphaSpeed;
	image = ImageManager::GetInstance()->FindImage("alphabackground");
}

void AlphaBackground::Update()
{
	Alpha -= 30.f * TimerManager::GetInstance()->GetDeltaTime();

	if (Alpha <= 0.f)
	{
		bDead = true;
		LevelManager::GetInstance()->SetNextLevelState(ELevelState::Main);
	}		
}

void AlphaBackground::Render(HDC hdc)
{
	if (image != nullptr && !bDead)
		image->FrameRenderAlpha(hdc, pos.x, pos.y, 0, 0, false, Alpha);
}

void AlphaBackground::Release()
{
}

AlphaBackground::~AlphaBackground()
{
}
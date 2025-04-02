#include "PressKey.h"
#include "Image.h"
#include "ImageManager.h"
#include "CommonFunction.h"

PressKey::PressKey()
	:RC(), Scale(0.f), Dir(1), Speed(1.f)
{
}

void PressKey::Init()
{
	pos.x = WINSIZE_X * 0.5f;
	pos.y = WINSIZE_Y * 0.85f;
	Scale = 1.f;
	Speed = 0.3f;

	image = ImageManager::GetInstance()->FindImage("pressKey");
	RC.left = pos.x - image->GetFrameWidth() * 0.5f;
	RC.top = pos.y - image->GetFrameHeight() * 0.5f;
	RC.right = pos.x + image->GetFrameWidth() * 0.5f;
	RC.bottom = pos.y + image->GetFrameHeight() * 0.5f;
}


void PressKey::Update()
{
	if (Scale >= 1.2f)
		Dir = -1;
	else if (Scale <= 1.f)
		Dir = 1;

	Scale += (Speed * TimerManager::GetInstance()->GetDeltaTime()) * Dir;
	if (image != nullptr)
		image->SetScale(Scale, Scale);
}

void PressKey::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
}

void PressKey::Release()
{
}

PressKey::~PressKey()
{
}
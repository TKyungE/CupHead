#include "BackGround.h"
#include "Image.h"
#include "ImageManager.h"

BackGround::BackGround()
	:Image(nullptr), Speed(0)
{
}

BackGround::~BackGround()
{
}

void BackGround::Init(FPOINT InPos, int InSpeed)
{
	pos = InPos;
	Speed = InSpeed;

	Image = ImageManager::GetInstance()->AddImage("blimp_sky", L"Image/CupHead/BackGround/blimp_sky.bmp", 1540, 900, 1, 1, true, RGB(255, 0, 255));
}

void BackGround::Update()
{
	if(Speed)
		pos.x = Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void BackGround::Render(HDC hdc)
{
	if (Image != nullptr)
		Image->FrameRender(hdc, pos.x, pos.y, 0, 0);
}

void BackGround::Release()
{
}
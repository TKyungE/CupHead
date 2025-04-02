#include "PotenUp.h"
#include "Image.h"
#include "ImageManager.h"
PotenUp::PotenUp()
{
}

void PotenUp::Init(float InX)
{
	pos.x = InX;
	pos.y = WINSIZE_Y * 0.5f;
	image = ImageManager::GetInstance()->FindImage("potenup");
}

void PotenUp::Update()
{
	pos.x += 300.f * TimerManager::GetInstance()->GetDeltaTime();

	if (pos.x - image->GetFrameWidth() * 0.5f >= WINSIZE_X)
		pos.x = -image->GetFrameWidth() * 0.5f;
}

void PotenUp::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
}

void PotenUp::Release()
{
}

PotenUp::~PotenUp()
{
}
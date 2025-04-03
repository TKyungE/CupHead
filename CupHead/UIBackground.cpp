#include "UIBackground.h"
#include "Image.h"
#include "ImageManager.h"

UIBackground::UIBackground()
{
}

void UIBackground::Init(string InKey)
{
	pos.x = WINSIZE_X * 0.5f;
	pos.y = WINSIZE_Y * 0.5f;

	image = ImageManager::GetInstance()->FindImage(InKey);
	
}

void UIBackground::Update()
{

}

void UIBackground::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
}

void UIBackground::Release()
{
}

UIBackground ::~UIBackground()
{
}

#include "UIBase.h"
#include "Image.h"
UIBase::UIBase()
{
}

void UIBase::Init()
{
	__super::Init();
}

void UIBase::Update()
{
	__super::Update();
}

void UIBase::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);
}

void UIBase::Release()
{
	__super::Release();
}

UIBase::~UIBase()
{
}
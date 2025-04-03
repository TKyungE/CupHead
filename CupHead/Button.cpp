#include "Button.h"
#include "Image.h"
#include "ImageManager.h"
#include "LevelManager.h"

Button::Button()
	:ButtonType(EButtonType::End), bHover(false)
{
}

void Button::Init(string InKey, float InX, float InY, EButtonType InButtonType)
{	
	ButtonType = InButtonType;
	pos.x = InX;
	pos.y = InY;

	image = ImageManager::GetInstance()->FindImage(InKey);
}

void Button::Update()
{
	if (bHover)
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE) || KeyManager::GetInstance()->IsStayKeyDown(VK_RETURN))
		{
			switch (ButtonType)
			{
			case EButtonType::ReTry:
				LevelManager::GetInstance()->ReTry();
				break;
			case EButtonType::Exit:
				PostQuitMessage(0);
				break;
			}
		}
		CurFrameIndex = 1;
	}
	else
		CurFrameIndex = 0;
}

void Button::Release()
{
}

Button::~Button()
{
}
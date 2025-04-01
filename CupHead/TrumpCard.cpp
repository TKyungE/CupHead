#include "TrumpCard.h"
#include "Image.h"
#include "ImageManager.h"
#include "CommonFunction.h"

TrumpCard::TrumpCard()
	:MaxCount(0), CurrentCount(0), MaxY(0), bTurn(false), FrameDir(1)
{
}

void TrumpCard::Init(FPOINT InPos, float InMaxCount)
{
	pos = InPos;
	DefaultPos = InPos;
	MaxCount = InMaxCount;

	FrameSpeed = 0.f;

	image = ImageManager::GetInstance()->AddImage("hud_ch_card_flip", L"Image/CupHead/UI/Player/Trump/hud_ch_card_flip.bmp", 120, 30, 6, 1, true, RGB(255, 0, 255));
	MaxY = (WINSIZE_Y - image->GetFrameHeight() * 0.5f);
}

void TrumpCard::Update()
{
	if (!MaxCount)
		return;

	UpdateFrame();

	const float dY = DefaultPos.y - float((image->GetFrameHeight() / MaxCount) * CurrentCount);
	pos.y = Lerp(pos.y, dY, 0.1f);

	if (bTurn && MaxCount == CurrentCount)
	{
		IsStayMaxFrame = false;
		FrameSpeed = 10.f;
	}
	else if (MaxCount == CurrentCount)
	{
		IsStayMaxFrame = true;
		FrameSpeed = 10.f;
	}
	else
	{
		bTurn = false;

		CurFrameIndex = 0;
		FrameSpeed = 0.f;
		FrameTime = 0.f;	
	}		
}

void TrumpCard::Render(HDC hdc)
{
	if (image)
		image->FrameRenderAlpha(hdc, pos.x, pos.y, CurFrameIndex, CurFrameYIndex, false, 255, MaxY);
}

void TrumpCard::UpdateFrame()
{
	if (!bTurn)
		__super::UpdateFrame();
	else
	{
		FrameTime +=  (FrameSpeed * TimerManager::GetInstance()->GetDeltaTime()) * FrameDir;
		CurFrameIndex = (int)FrameTime;

		if (CurFrameIndex >= image->GetMaxFrameX())
		{
			CurFrameIndex = image->GetMaxFrameX() - 1;
			FrameDir = -1;
		}
			
		else if (FrameDir == -1 && CurFrameIndex < 0)
		{
			CurFrameIndex = 0;
			FrameDir = 1;
		}
	}
}

void TrumpCard::Release()
{
}

TrumpCard::~TrumpCard()
{
}
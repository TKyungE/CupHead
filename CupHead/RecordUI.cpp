#include "RecordUI.h"
#include "Image.h"
#include "ImageManager.h"
#include "SimpleUI.h"
#include "ObjectManager.h"

RecordUI::RecordUI()
	:CurrentTime(0.f), DelayTime(0.f), CurrentFrameCount(0), FrameCount(0), RecordTime(0.f)
{
}

void RecordUI::Init(string InKey,float InX, float InY, float InRecordTime, float InDelayTime, int InFrameCount)
{
	FrameSpeed = 10.f;

	pos.x = InX;
	pos.y = InY;
	DelayTime = InDelayTime;
	FrameCount = InFrameCount;
	RecordTime = InRecordTime;

	image = ImageManager::GetInstance()->FindImage(InKey);

	CurFrameIndex = FrameTime = image->GetMaxFrameX() - 1;
}

void RecordUI::Update()
{
	if(CurrentTime < DelayTime)
		CurrentTime += TimerManager::GetInstance()->GetDeltaTime();

	if (CurrentTime >= DelayTime && CurrentFrameCount < FrameCount)
	{
		UpdateFrame();

		if (CurrentFrameCount >= FrameCount)
		{
			// 진짜 기록에 따른 CurFrameIndex를 설정 A = 0, B = 1, C = 2, D = 3
			if (RecordTime < 1.f * 60.f) // 1분
				CurFrameIndex = 0;
			else if (RecordTime < 2.f * 60.f)
				CurFrameIndex = 1;
			else if (RecordTime < 3.f * 60.f)
				CurFrameIndex = 2;
			else
				CurFrameIndex = 3;

			// UIEffect
			SimpleUI* puffFx = new SimpleUI();
			puffFx->Init("result_fx_puff",20.f,pos.x,pos.y, 1,false,false);
			ObjectManager::GetInstance()->AddObject(puffFx, OBJ_UI);

			SimpleUI* starFx = new SimpleUI();
			starFx->Init("result_star", 20.f, pos.x, pos.y, 1,false, false);
			ObjectManager::GetInstance()->AddObject(starFx, OBJ_UI);			

			SimpleUI* circleFx = new SimpleUI();
			circleFx->Init("winscreen_circle", 10.f, pos.x, pos.y, -1, false, false);
			ObjectManager::GetInstance()->AddObject(circleFx, OBJ_UI);			
		}
	}
}

void RecordUI::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);
}

void RecordUI::UpdateFrame()
{
	FrameTime -= FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex < 0)
	{
		CurFrameIndex = FrameTime = image->GetMaxFrameX() - 1;

		++CurrentFrameCount;
	}
}

void RecordUI::Release()
{
}

RecordUI::~RecordUI()
{
}
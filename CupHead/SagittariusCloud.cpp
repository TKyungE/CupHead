#include "SagittariusCloud.h"
#include "Image.h"
#include "ImageManager.h"

SagittariusCloud::SagittariusCloud()
	:Owner(nullptr), Pivot({0.f,0.f})
{
}

void SagittariusCloud::Init(GameObject* InOwner, FPOINT InPivot)
{
	Owner = InOwner;
	Pivot = InPivot;

	FrameSpeed = 10.f;

	image = ImageManager::GetInstance()->AddImage("sagg_cloud_top", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Cloud/Top/sagg_cloud_top.bmp", 5124, 257, 12, 1, true, RGB(255, 0, 255));
}


void SagittariusCloud::Update()
{
	UpdateFrame();

	if (Owner != nullptr)
	{
		pos.x = Owner->GetPos().x + Pivot.x;
		pos.y = Owner->GetPos().y + Pivot.y;
	}		
}

void SagittariusCloud::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);
}

void SagittariusCloud::Release()
{
}
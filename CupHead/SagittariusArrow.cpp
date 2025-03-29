#include "SagittariusArrow.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "CommonFunction.h"

SagittariusArrow::SagittariusArrow(FPOINT pos, FPOINT size)
{
	this->pos = pos;
	this->size = size;
}

void SagittariusArrow::Init()
{
	Speed = 500.f;
	FrameSpeed = 10.f;

	image = ImageManager::GetInstance()->AddImage("sagg_arrow", L"Image/CupHead/Hilda Berg/Sagittarius/Arrow/Arrow/sagg_arrow.bmp", 3376, 72, 8, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { (float)image->GetFrameWidth() * 0.5f,0.f }, {(float)image->GetFrameWidth(),(float)image->GetFrameHeight()}, true, 2.f);
	collider->Init(); 
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER_WEAPON);
}

void SagittariusArrow::Update()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	if (CurFrameIndex >= image->GetMaxFrameX())
	{
		if (true == IsStayMaxFrame)
			CurFrameIndex = image->GetMaxFrameX() - 1;
		else
			CurFrameIndex = FrameTime = 0.f;
	}

	Move();

	if (OutOfScreen(FPOINT{ pos.x + image->GetFrameWidth() * 0.5f, pos.y }, image->GetFrameWidth(), image->GetFrameHeight()))
		bDead = true;
}

void SagittariusArrow::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y - image->GetFrameHeight() * 0.5f, CurFrameIndex);
}

void SagittariusArrow::Move()
{
	pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void SagittariusArrow::Release()
{
}
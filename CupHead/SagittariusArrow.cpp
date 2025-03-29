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
	//float image->GetWidth() / image->GetMaxFrameX(), (float)image->GetHeight() / image->GetMaxFrameY();
	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { (float)image->GetWidth() / image->GetMaxFrameX() * 0.5f,0.f }, {(float)image->GetWidth() / image->GetMaxFrameX(),(float)image->GetHeight() / image->GetMaxFrameY()}, true, 2.f);
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

	if (OutOfScreen(FPOINT{ pos.x + image->GetWidth() / image->GetMaxFrameX() * 0.5f, pos.y }, image->GetWidth() / image->GetMaxFrameX(), image->GetHeight()))
		bDead = true;
}

void SagittariusArrow::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y - image->GetHeight() / image->GetMaxFrameY() * 0.5f, CurFrameIndex);
}

void SagittariusArrow::Move()
{
	pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void SagittariusArrow::Release()
{
}
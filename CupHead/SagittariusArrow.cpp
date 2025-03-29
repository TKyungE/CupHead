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

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { (float)image->GetFrameWidth(),(float)image->GetFrameHeight() }, true, 2.f);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER_WEAPON);
}

void SagittariusArrow::Update()
{
	UpdateFrame();

	Move();

	if (OutOfScreen(pos, image->GetFrameWidth(), image->GetFrameHeight()))
		bDead = true;
}

void SagittariusArrow::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0);
}

void SagittariusArrow::Move()
{
	pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void SagittariusArrow::Release()
{
}
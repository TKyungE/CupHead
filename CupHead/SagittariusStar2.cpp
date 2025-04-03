#include "SagittariusStar2.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"


SagittariusStar2::SagittariusStar2()
	:Angle(0.f), ImageSize(0.f)
{
	TrailImages[0] = "a_sagg_star_trail";
	TrailImages[1] = "b_sagg_star_trail";
	TrailImages[2] = "c_sagg_star_trail";
}

void SagittariusStar2::Init(string InKey, float InX, float InY, float InSpeed)
{
	pos.x = InX;
	pos.y = InY;

	Speed = InSpeed;
	FrameSpeed = 20.f;

	MaxHp = 1;
	Hp = MaxHp;

	image = ImageManager::GetInstance()->FindImage(InKey);
	ImageSize = sqrtf(powf(image->GetFrameWidth(), 2) + powf(image->GetFrameHeight(), 2));

	list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJTYPE::OBJ_PLAYER);
	if (!playerList.empty())
	{
		GameObject* player = playerList.front();
		Angle = atan2f(player->GetPos().y - pos.y, player->GetPos().x - pos.x);
	}

	Collider* collider = new Collider(this, COLLIDERTYPE::Sphere, { 0.f,0.f }, 30.f, true, 0.5f);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER);
}

void SagittariusStar2::Update()
{
	UpdateFrame();

	Move();
	TrailUpdate();
}

void SagittariusStar2::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, CurFrameYIndex);
}

void SagittariusStar2::Move()
{
	pos.x += Speed * cosf(Angle) * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += Speed * sinf(Angle) * TimerManager::GetInstance()->GetDeltaTime();

	if (OutOfScreen(pos, image->GetFrameWidth(), image->GetFrameHeight()))
		bDead = true;
}

void SagittariusStar2::TakeDamage(int damage)
{
	if (Hp == 0)
		return;
	Hp = max(0, Hp - damage);
	if (Hp <= 0)
	{
		bDead = true;
		EffectManager::GetInstance()->AddEffect("sagg_star_death", pos, 1.f);
	}
}

void SagittariusStar2::TrailUpdate()
{
	const float distance = sqrtf(powf(pos.x - TrailPos.x, 2) + powf(pos.y - TrailPos.y, 2));

	if (!bDead && distance >= ImageSize * 0.3f)
	{
		const int ImageIndex = uid(dre) % 3;
		EffectManager::GetInstance()->AddEffect(TrailImages[ImageIndex], TrailPos, 0.75f);
		TrailPos = pos;
	}
}

void SagittariusStar2::Release()
{
}
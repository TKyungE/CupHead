#include "UFO.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "UFOBeam.h"
#include "ObjectManager.h"
#include "CommonFunction.h"

UFO::UFO()
	:bAttack(false), UFOBeamWeapon(nullptr)
{
}

void UFO::Init(FPOINT pos)
{
	this->pos = pos;
	Speed = 300.f;
	FrameSpeed = 15.f;

	const bool UFOBronze = bool(uid(dre) % 2);
	if (UFOBronze)
		image = ImageManager::GetInstance()->AddImage("bronze_blimp_moon_ufo", L"Image/CupHead/Hilda Berg/Moon/Attack/bronze_blimp_moon_ufo.bmp", 3360, 75, 16, 1, true, RGB(255, 0, 255));
	else
		image = ImageManager::GetInstance()->AddImage("blimp_moon_ufo", L"Image/CupHead/Hilda Berg/Moon/Attack/blimp_moon_ufo.bmp", 3360, 75, 16, 1, true, RGB(255, 0, 255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, {0.f,0.f}, { (float)image->GetFrameWidth(),(float)image->GetFrameHeight() }, true, 2.f);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER);
}

void UFO::Update()
{
	UpdateFrame();

	Move();
	Attack();

	if (OutOfScreen(pos, image->GetFrameWidth(), image->GetFrameHeight()))
		bDead = true;
}

void UFO::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex,0);	
}

void UFO::Move()
{
	pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();

	if (WINSIZE_X - pos.x >= 150.f && pos.y - (image->GetFrameHeight() * 0.5f) >= 0.f)
	{
		pos.y -= Speed * TimerManager::GetInstance()->GetDeltaTime();

		if (pos.y - (image->GetFrameHeight() * 0.5f) < 0.f)
			pos.y = image->GetFrameHeight() * 0.5f;
	}		
}

void UFO::Attack()
{
	if (bAttack)
		return;

	list<GameObject*> players = ObjectManager::GetInstance()->GetObjectList(OBJTYPE::OBJ_PLAYER);

	if (!players.empty())
	{
		GameObject* player = players.front();

		const FPOINT playerPos = player->GetPos();
		if (abs(playerPos.x - pos.x) <= 300.f)
		{
			bAttack = true;

			if (UFOBeamWeapon == nullptr)
			{
				UFOBeamWeapon = new UFOBeam();
				UFOBeamWeapon->Init(this,{0.f,(float)image->GetFrameWidth()});
				ObjectManager::GetInstance()->AddObject(UFOBeamWeapon,OBJ_MONSTER_WEAPON);
			}
		}
	}
}

void UFO::Release()
{
}
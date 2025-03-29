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
	Speed = 200.f;
	FrameSpeed = 15.f;

	image = ImageManager::GetInstance()->AddImage("blimp_moon_ufo", L"Image/CupHead/Hilda Berg/Moon/Attack/blimp_moon_ufo.bmp", 3360, 75, 16,1,true,RGB(255,0,255));

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { image->GetFrameWidth() * 0.5f,image->GetFrameHeight() * 0.5f}, { (float)image->GetFrameWidth(),(float)image->GetFrameHeight() }, true, 2.f);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER);
}

void UFO::Update()
{
	UpdateFrame();

	Move();
	Attack();

	if (OutOfScreen(FPOINT{ pos.x + image->GetFrameWidth() * 0.5f,pos.y}, image->GetFrameWidth(), image->GetFrameHeight()))
		bDead = true;

	if (UFOBeamWeapon != nullptr)
		UFOBeamWeapon->Update(pos);
}

void UFO::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y, CurFrameIndex);

	if (UFOBeamWeapon != nullptr)
		UFOBeamWeapon->Render(hdc);
}

void UFO::Move()
{
	pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();

	if (WINSIZE_X - pos.x >= 100.f && pos.y >= 0.f)
		pos.y -= Speed * TimerManager::GetInstance()->GetDeltaTime();
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
		if (abs(playerPos.x - pos.x) <= 20.f)
		{
			bAttack = true;

			if (UFOBeamWeapon == nullptr)
			{
				UFOBeamWeapon = new UFOBeam();
				UFOBeamWeapon->Init();
			}
		}
	}
}

void UFO::Release()
{
	if (UFOBeamWeapon != nullptr)
	{
		UFOBeamWeapon->Release();
		delete UFOBeamWeapon;
		UFOBeamWeapon = nullptr;
	}
}
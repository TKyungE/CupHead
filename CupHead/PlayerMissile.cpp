#include "PlayerMissile.h"
#include "Image.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "Player.h"

PlayerMissile::PlayerMissile() : Damage(1)
{

}

PlayerMissile::~PlayerMissile()
{
}

void PlayerMissile::Init(FPOINT _Pos, int _Damage)
{
	pos = _Pos;
	Damage = _Damage;
}

void PlayerMissile::Init()
{
}

void PlayerMissile::Release()
{
}

void PlayerMissile::Update()
{
	UpdateFrame();
	Move();
}

void PlayerMissile::Render(HDC hdc)
{
	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
}

void PlayerMissile::Move()
{

}

void PlayerMissile::TakeDamage(int damage)
{
	list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJ_PLAYER);

	if (!playerList.empty())
	{
		dynamic_cast<Player*>(playerList.front())->PlusSkillPoint(Damage);
	}
}

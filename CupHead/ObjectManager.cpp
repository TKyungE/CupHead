#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Orb.h"
#include "OrbBullet.h"

void ObjectManager::Init()
{
	// 테스트 코드 플레이어 생성
	Player* player = new Player();
	player->Init({100.f,100.f},{30.f,30.f});
	AddObject(player, OBJTYPE::OBJ_PLAYER);


	//Orb* orb = new Orb({700.f,300.f},30.f);
	//orb->Init();
	//AddObject(orb, OBJTYPE::OBJ_MONSTER);

	OrbBullet* orbBullet = new OrbBullet({ 100.f,300.f });
	orbBullet->Init();
	AddObject(orbBullet, OBJTYPE::OBJ_MONSTER_WEAPON);
}

void ObjectManager::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = ObjectList[i].begin(); iter != ObjectList[i].end();)
		{
			(*iter)->Update();
			if ((*iter)->IsDead())
			{
				(*iter)->Release();
				delete (*iter);
				iter = ObjectList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : ObjectList[i])
		{
			iter->Render(hdc);
		}
	}
}

void ObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : ObjectList[i])
		{
			iter->Release();
			delete iter;
		}
		ObjectList[i].clear();
	}

	ReleaseInstance();
}

#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BlimpEnemy.h"

void ObjectManager::Init()
{
	// 테스트 코드 플레이어 생성
	//Player* player = new Player();
	//player->Init({100.f,100.f},{30.f,30.f});
	//AddObject(player, OBJTYPE::OBJ_PLAYER);

	// 테스트 코드 BlimpEnemy 생성
	BlimpEnemy* blimpEnemy = new BlimpEnemy();
	blimpEnemy->Init();
	blimpEnemy->SetColor(BlimpEnemyInfo::colors[BlimpEnemyInfo::EColor::GREEN]);
	AddObject(blimpEnemy, OBJTYPE::OBJ_MONSTER);
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

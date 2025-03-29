#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BlimpEnemy.h"
#include "UFO.h"

void ObjectManager::Init()
{
	// 김태경 테스트 코드
	{
		// 테스트 코드 플레이어 생성
		Player* player = new Player();
		player->Init({ 100.f,100.f }, { 30.f,30.f });
		AddObject(player, OBJTYPE::OBJ_PLAYER);

		// 테스트 코드 UFO 생성
		UFO* ufo = new UFO();
		ufo->Init({ WINSIZE_X,300.f });
		AddObject(ufo, OBJTYPE::OBJ_MONSTER);
	}



	// 테스트 코드 BlimpEnemy 생성
	BlimpEnemy* blimpEnemy = new BlimpEnemy();
	blimpEnemy->Init(BlimpEnemyInfo::EColor::GREEN, 5);
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
				(*iter) = nullptr;
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
			iter = nullptr;
		}
		ObjectList[i].clear();
	}

	ReleaseInstance();
}

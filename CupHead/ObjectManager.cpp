#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BlimpEnemy.h"
#include "Sagittarius.h"
#include "Moon.h"
#include "PlayerHP.h"
#include "KnockOut.h"
#include "HildaBlimp.h"

void ObjectManager::Init()
{
	// 김태경 테스트 코드
	{
		// 테스트 코드 플레이어 생성
		Player* player = new Player();
		player->Init({ 100.f,100.f }, { 30.f,30.f });
		AddObject(player, OBJTYPE::OBJ_PLAYER);

		//// 테스트 코드 Sagittarius 생성
		//Sagittarius* sagittarius = new Sagittarius();
		//sagittarius->Init({ WINSIZE_X * 0.8f,300.f });
		//AddObject(sagittarius, OBJTYPE::OBJ_MONSTER);

		// 테스트 코드 Moon 생성
		Moon* moon = new Moon();
		moon->Init();
		AddObject(moon, OBJTYPE::OBJ_MONSTER);

		// 테스트 코드 PlayerHP 생성
		PlayerHP* playerHP = new PlayerHP();
		playerHP->Init();
		AddObject(playerHP, OBJTYPE::OBJ_UI);

		// 테스트 코드 KnockOut 생성
		KnockOut* knockOut = new KnockOut();
		knockOut->Init();
		AddObject(knockOut, OBJTYPE::OBJ_UI);
	}

	// Test. BlimpEnemy
	BlimpEnemy* blimpEnemy = new BlimpEnemy();
	blimpEnemy->Init(BlimpEnemyInfo::EColor::GREEN, 5);
	AddObject(blimpEnemy, OBJTYPE::OBJ_MONSTER);

	// Test. HildaBlimp
	HildaBlimp* hilda = new HildaBlimp(2);
	hilda->Init({ WINSIZE_X - 200.f, WINSIZE_Y / 2.f });
	AddObject(hilda, OBJTYPE::OBJ_MONSTER);
}

void ObjectManager::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = ObjectList[i].begin(); iter != ObjectList[i].end();)
		{
			if ((*iter)->IsDead())
			{
				(*iter)->Release();
				delete (*iter);
				(*iter) = nullptr;
				iter = ObjectList[i].erase(iter);
			}
			else
			{
				(*iter)->Update();
				++iter;
			}				
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	RenderObject(hdc);
	RenderUI(hdc);
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

void ObjectManager::RenderObject(HDC hdc)
{
	for (auto& iter : ObjectList[OBJ_PLAYER])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_MONSTER])
		iter->Render(hdc);

	for(auto& iter : ObjectList[OBJ_PLAYER_WEAPON])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_MONSTER_WEAPON])
		iter->Render(hdc);
}

void ObjectManager::RenderUI(HDC hdc)
{
	for (auto& iter : ObjectList[OBJ_UI])
		iter->Render(hdc);
}

#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "BlimpEnemy.h"
#include "Sagittarius.h"
#include "Moon.h"
#include "PlayerHP.h"
#include "KnockOut.h"
#include "TrumpCardManager.h"
#include "ReadyWallop.h"

void ObjectManager::Init()
{
	// ���°� �׽�Ʈ �ڵ�
	{
		// �׽�Ʈ �ڵ� �÷��̾� ����
		Player* player = new Player();
		player->Init({ 100.f,100.f }, { 30.f,30.f });
		AddObject(player, OBJTYPE::OBJ_PLAYER);

		//// �׽�Ʈ �ڵ� Sagittarius ����
		Sagittarius* sagittarius = new Sagittarius();
		sagittarius->Init({ WINSIZE_X * 0.8f,300.f });
		AddObject(sagittarius, OBJTYPE::OBJ_MONSTER);

		// �׽�Ʈ �ڵ� Moon ����
	/*	Moon* moon = new Moon();
		moon->Init();
		AddObject(moon, OBJTYPE::OBJ_MONSTER);*/

		// �׽�Ʈ �ڵ� PlayerHP ����
		PlayerHP* playerHP = new PlayerHP();
		playerHP->Init();
		AddObject(playerHP, OBJTYPE::OBJ_UI);

		// �׽�Ʈ �ڵ� KnockOut ����
	/*	KnockOut* knockOut = new KnockOut();
		knockOut->Init();
		AddObject(knockOut, OBJTYPE::OBJ_UI);*/

		// �׽�Ʈ �ڵ� TrumpCardManager ����
		TrumpCardManager* trumpCardManager = new TrumpCardManager();
		trumpCardManager->Init(10, 5);
		AddObject(trumpCardManager, OBJTYPE::OBJ_ETC);

		// �׽�Ʈ �ڵ� KnockOut ����
		ReadyWallop* readyWallop = new ReadyWallop();
		readyWallop->Init();
		AddObject(readyWallop, OBJTYPE::OBJ_UI);
	}

	// �׽�Ʈ �ڵ� BlimpEnemy ����
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

	for (auto& iter : ObjectList[OBJ_PLAYER_WEAPON])
		iter->Render(hdc);

	for (auto& iter : ObjectList[OBJ_MONSTER_WEAPON])
		iter->Render(hdc);
}

void ObjectManager::RenderUI(HDC hdc)
{
	for (auto& iter : ObjectList[OBJ_UI])
		iter->Render(hdc);
}

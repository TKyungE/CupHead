#include "Level1.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "BackGround.h"
#include "Fade.h"
#include "Tornado.h"
#include "LaughProjectile.h"
#include "Player.h"
#include "BlimpEnemy.h"
#include "Sagittarius.h"
#include "Moon.h"
#include "PlayerHP.h"
#include "KnockOut.h"
#include "TrumpCardManager.h"
#include "ReadyWallop.h"
#include "HildaBerg.h"

Level1::Level1()
	:BackgroundManager(nullptr), ObjectManager(nullptr), CollisionManager(nullptr), EffectManager(nullptr), CurrentTime(0.f)
{
}


void Level1::Init(void* InData)
{
	BackgroundManager = new BackGroundManager;
	BackgroundManager->Init();

	ObjectManager = ObjectManager::GetInstance();
	ObjectManager->Init();

	CollisionManager = CollisionManager::GetInstance();
	CollisionManager->Init();

	EffectManager = EffectManager::GetInstance();
	EffectManager->Init();

	ImageInit();
	ObjectInit();
}

void Level1::Update()
{
	// 클리어 누적 시간 
	CurrentTime += TimerManager::GetInstance()->GetDeltaTime();

	if (LevelManager::GetInstance()->GetNextLevelState() != LevelManager::GetInstance()->GetLevelState())
	{
		LevelManager::GetInstance()->SetLevelState(LevelManager::GetInstance()->GetNextLevelState());
		return;
	}

	TestCode();

	if (BackgroundManager != nullptr)
		BackgroundManager->Update();

	if (ObjectManager != nullptr)
		ObjectManager->Update();

	if (CollisionManager != nullptr)
		CollisionManager->Update();

	if (EffectManager != nullptr)
		EffectManager->Update();
}

void Level1::Render(HDC hdc)
{
	if (BackgroundManager != nullptr)
		BackgroundManager->RenderBackGround(hdc);

	if (ObjectManager != nullptr)
		ObjectManager->Render(hdc);

	if (CollisionManager != nullptr)
		CollisionManager->Render(hdc);

	if (EffectManager != nullptr)
		EffectManager->Render(hdc);

	if (BackgroundManager != nullptr)
		BackgroundManager->RenderForeGround(hdc);

	if (ObjectManager != nullptr)
		ObjectManager->RenderUI(hdc);
}

void Level1::ObjectInit(void* InData)
{
	// 김태경 테스트 코드
	{
		// 테스트 코드 플레이어 생성
		Player* player = new Player();
		player->Init({ 100.f,100.f }, { 105.f, 95.f });
		ObjectManager->AddObject(player, OBJTYPE::OBJ_PLAYER);

		//// 테스트 코드 Sagittarius 생성
	/*	Sagittarius* sagittarius = new Sagittarius();
		sagittarius->Init({ WINSIZE_X * 0.8f,300.f });
		ObjectManager->AddObject(sagittarius, OBJTYPE::OBJ_MONSTER);*/

		// 테스트 코드 Moon 생성
	/*	Moon* moon = new Moon();
		moon->Init();
		ObjectManager->AddObject(moon, OBJTYPE::OBJ_MONSTER);*/

		// 테스트 코드 PlayerHP 생성
		PlayerHP* playerHP = new PlayerHP();
		playerHP->Init();
		ObjectManager->AddObject(playerHP, OBJTYPE::OBJ_UI);

		// 테스트 코드 KnockOut 생성
	/*	KnockOut* knockOut = new KnockOut();
		knockOut->Init();
		AddObject(knockOut, OBJTYPE::OBJ_UI);*/

		// 테스트 코드 TrumpCardManager 생성
		TrumpCardManager* trumpCardManager = new TrumpCardManager();
		trumpCardManager->Init(10, 50);
		ObjectManager->AddObject(trumpCardManager, OBJTYPE::OBJ_ETC);

		// 테스트 코드 KnockOut 생성
		ReadyWallop* readyWallop = new ReadyWallop();
		readyWallop->Init();
		ObjectManager->AddObject(readyWallop, OBJTYPE::OBJ_UI);
	}

	// 테스트 코드 HildaBerg 생성
	HildaBerg* hilda = new HildaBerg();
	hilda->Init();
	ObjectManager->AddObject(hilda, OBJTYPE::OBJ_MONSTER);

	Fade* fade = new Fade();
	fade->Init(EFadeMode::FadeIn);
	ObjectManager->AddObject(fade, OBJTYPE::OBJ_UI);
}

void Level1::ImageInit()
{
	ImageManager::GetInstance()->AddImage("FightText_GetReady", L"Image/CupHead/UI/FightText_GetReady.bmp", 25600, 288, 50, 1, true, RGB(255, 0, 255));

}

void Level1::TestCode()
{
	// Test Star
	//srand(time(NULL));
	//if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	//{
	//	for (int i = 0; i < 3; ++i)
	//	{
	//		
	//		StarProjectile* star = new StarProjectile(StarType(i));
	//		star->Init({ mousePos.x, float(mousePos.y + (i - 1) * 150) });
	//		Objectmanager->AddObject(star, OBJTYPE::OBJ_MONSTER_WEAPON);
	//	}
	//}
	// 
	// Test Laugh
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	{
		LaughProjectile* Laugh = new LaughProjectile();
		Laugh->Init(g_MousePos);
		ObjectManager::GetInstance()->AddObject(Laugh, OBJTYPE::OBJ_MONSTER_WEAPON);
	}
}

void Level1::Release()
{
	if (BackgroundManager != nullptr)
	{
		BackgroundManager->Release();
		delete BackgroundManager;
		BackgroundManager = nullptr;
	}

	if (CollisionManager != nullptr)
	{
		CollisionManager->Release();
		CollisionManager = nullptr;
	}

	if (ObjectManager != nullptr)
	{
		ObjectManager->Release();
		ObjectManager = nullptr;
	}

	if (EffectManager != nullptr)
	{
		EffectManager->Release();
		EffectManager = nullptr;
	}

	LevelManager::GetInstance()->SetData(new float(CurrentTime));
}

Level1::~Level1()
{
}
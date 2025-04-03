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
#include "DeathCard.h"
#include "Image.h"

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

		// 테스트 코드 PlayerHP 생성
		PlayerHP* playerHP = new PlayerHP();
		playerHP->Init();
		ObjectManager->AddObject(playerHP, OBJTYPE::OBJ_UI);

		// 테스트 코드 ReadyWallop 생성
		ReadyWallop* readyWallop = new ReadyWallop();
		readyWallop->Init();
		ObjectManager->AddObject(readyWallop, OBJTYPE::OBJ_UI);

		Fade* fade = new Fade();
		fade->Init(EFadeMode::FadeIn);
		ObjectManager->AddObject(fade, OBJTYPE::OBJ_UPPERUI);
	}

	// 테스트 코드 HildaBerg 생성
	HildaBerg* hilda = new HildaBerg();
	hilda->Init();
	ObjectManager->AddObject(hilda, OBJTYPE::OBJ_MONSTER);	
}

void Level1::ImageInit()
{
	Image* image = nullptr;
	ImageManager::GetInstance()->AddImage("FightText_GetReady", L"Image/CupHead/UI/FightText_GetReady.bmp", 25600, 288, 50, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("death_card_bg", L"Image/CupHead/UI/Menu/death_card_bg.bmp", 595, 668, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("death_card_mugshot_blimp1", L"Image/CupHead/UI/Menu/death_card_mugshot_blimp1.bmp", 221, 227, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("death_card_mugshot_moon", L"Image/CupHead/UI/Menu/death_card_mugshot_moon.bmp", 225, 219, 1, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("DeathText1", L"Image/CupHead/UI/Menu/DeathText1.bmp", 1000, 168, 1, 1, true, RGB(255, 0, 255));
	image->SetScale(0.3f, 0.3f);
	image = ImageManager::GetInstance()->AddImage("DeathText2", L"Image/CupHead/UI/Menu/DeathText2.bmp", 1353, 168, 1, 1, true, RGB(255, 0, 255));
	image->SetScale(0.3f, 0.3f);
	image = ImageManager::GetInstance()->AddImage("DeathText3", L"Image/CupHead/UI/Menu/DeathText3.bmp", 1436, 168, 1, 1, true, RGB(255, 0, 255));
	image->SetScale(0.3f, 0.3f);

	image = ImageManager::GetInstance()->AddImage("ReTry", L"Image/CupHead/UI/Menu/ReTry.bmp", 578, 72, 2, 1, true, RGB(255, 0, 255));
	image->SetScale(0.3f, 0.3f);
	image =ImageManager::GetInstance()->AddImage("Exit", L"Image/CupHead/UI/Menu/Exit.bmp", 598, 71, 2, 1, true, RGB(255, 0, 255));
	image->SetScale(0.3f, 0.3f);

	image = ImageManager::GetInstance()->AddImage("phaseIndex", L"Image/CupHead/UI/Menu/phaseIndex.bmp", 7, 27, 1, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetInstance()->AddImage("death_card_run", L"Image/CupHead/UI/Menu/death_card_run.bmp", 864, 62, 16, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetInstance()->AddImage("phaseIndex", L"Image/CupHead/UI/Menu/phaseIndex.bmp", 7, 27, 1, 1, true, RGB(255, 0, 255));
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

	if (KeyManager::GetInstance()->IsOnceKeyDown('0'))
	{
		DeathCard* deathCard = new DeathCard();
		deathCard->Init("death_card_bg", WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f);
		ObjectManager->AddObject(deathCard, OBJTYPE::OBJ_UI);
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
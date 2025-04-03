#include "LevelMain.h"
#include "ObjectManager.h"
#include "MainTitle.h"
#include "PressKey.h"
#include "LevelManager.h"
#include "Fade.h"


LevelMain::LevelMain()
	:ObjectManager(nullptr)
{
}


void LevelMain::Init(void* InData)
{
	ObjectManager = ObjectManager::GetInstance();
	ObjectManager->Init();

	ImageInit();
	ObjectInit();
}

void LevelMain::Update()
{
	if (LevelManager::GetInstance()->GetNextLevelState() != LevelManager::GetInstance()->GetLevelState())
	{
		LevelManager::GetInstance()->SetLevelState(LevelManager::GetInstance()->GetNextLevelState());
		return;
	}

	for (int i = 0; i < MAX_KEY_COUNT; ++i)
	{
		if (i == 21)
			continue;
		if (KeyManager::GetInstance()->IsOnceKeyDown(i))
		{
			Fade* fade = new Fade();
			fade->Init(EFadeMode::FadeOut, ELevelState::Level1);
			ObjectManager->AddObject(fade, OBJ_UPPERUI);
			break;
		}			
	}

	if (ObjectManager != nullptr)
		ObjectManager->Update();
}

void LevelMain::Render(HDC hdc)
{
	if (ObjectManager != nullptr)
	{
		ObjectManager->Render(hdc);
		ObjectManager->RenderUI(hdc);
	}		
}

void LevelMain::ImageInit()
{
	ImageManager::GetInstance()->AddImage("cuphead_title_screen", L"Image/CupHead/UI/Screen/Title/cuphead_title_screen.bmp", 37162, 622, 34, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("title_screen_background", L"Image/CupHead/UI/Screen/Title/title_screen_background.bmp", 1280, 720, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("pressKey", L"Image/CupHead/UI/Screen/Title/pressKey.bmp", 460, 215, 1, 1, true, RGB(255, 0, 255));
}

void LevelMain::ObjectInit(void* InData)
{
	MainTitle* mainTitle = new MainTitle();
	mainTitle->Init();
	ObjectManager->AddObject(mainTitle, OBJ_UI);

	PressKey* pressKey = new PressKey();
	pressKey->Init();
	ObjectManager->AddObject(pressKey, OBJ_UI);
}

void LevelMain::Release()
{
	if (ObjectManager != nullptr)
	{
		ObjectManager->Release();
		ObjectManager = nullptr;
	}
}

LevelMain::~LevelMain()
{
}
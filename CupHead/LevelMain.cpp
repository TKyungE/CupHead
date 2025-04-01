#include "LevelMain.h"
#include "MainTitle.h"
#include "ObjectManager.h"

LevelMain::LevelMain()
	:ObjectManager(nullptr)
{
}


void LevelMain::Init()
{
	ObjectManager = ObjectManager::GetInstance();
	ObjectManager->Init();

	ImageInit();
	ObjectInit();
}

void LevelMain::Update()
{
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
}

void LevelMain::ObjectInit()
{
	MainTitle* mainTitle = new MainTitle();
	mainTitle->Init();
	ObjectManager->AddObject(mainTitle, OBJ_UI);
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
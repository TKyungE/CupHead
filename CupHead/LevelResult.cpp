#include "LevelResult.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "UIBackground.h"
#include "SimpleUI.h"

LevelResult::LevelResult()
	:ObjectManager(nullptr)
{
}

void LevelResult::Init()
{
	ObjectManager = ObjectManager::GetInstance();
	ObjectManager->Init();

	ImageInit();
	ObjectInit();	
}

void LevelResult::Update()
{
	if (LevelManager::GetInstance()->GetNextLevelState() != LevelManager::GetInstance()->GetLevelState())
	{
		LevelManager::GetInstance()->SetLevelState(LevelManager::GetInstance()->GetNextLevelState());
		return;
	}

	if (ObjectManager != nullptr)
		ObjectManager->Update();
}

void LevelResult::Render(HDC hdc)
{
	if (ObjectManager != nullptr)
		ObjectManager->RenderUI(hdc);
}

void LevelResult::ImageInit()
{
	ImageManager::GetInstance()->AddImage("winscreen_bg", L"Image/CupHead/UI/Screen/Win/winscreen_bg.bmp", 1583, 1520, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("winscreen_board", L"Image/CupHead/UI/Screen/Win/winscreen_board.bmp", 566, 458, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("winscreen_ch", L"Image/CupHead/UI/Screen/Win/winscreen_ch.bmp", 2107, 433, 7, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("winscreen_results_title_a", L"Image/CupHead/UI/Screen/Win/winscreen_results_title_a.bmp", 2376, 150, 3, 1, true, RGB(255, 0, 255));
}

void LevelResult::ObjectInit()
{
	if (ObjectManager == nullptr)
		return;
	UIBackground* resultBackground = new UIBackground();
	resultBackground->Init("winscreen_bg");

	ObjectManager->AddObject(resultBackground, OBJ_UI);

	SimpleUI* board = new SimpleUI();
	board->Init("winscreen_board",0.f,WINSIZE_X * 0.5f,WINSIZE_Y * 0.5f);
	ObjectManager->AddObject(board, OBJ_UI);

	SimpleUI* result = new SimpleUI();
	result->Init("winscreen_results_title_a", 10.f, WINSIZE_X * 0.5f, 75.f);
	ObjectManager->AddObject(result, OBJ_UI);

	SimpleUI* cupHead = new SimpleUI();
	cupHead->Init("winscreen_ch", 20.f, WINSIZE_X * 0.5f, WINSIZE_Y * 0.5f,true);
	ObjectManager->AddObject(cupHead, OBJ_UI);

}

void LevelResult::Release()
{
	if (ObjectManager != nullptr)
	{
		ObjectManager->Release();
		ObjectManager = nullptr;
	}
}

LevelResult::~LevelResult()
{
}

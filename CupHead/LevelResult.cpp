#include "LevelResult.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "UIBackground.h"
#include "SimpleUI.h"
#include "RecordUI.h"
#include "Fade.h"

LevelResult::LevelResult()
	:ObjectManager(nullptr), CurrentTime(0.f)
{
}

void LevelResult::Init(void* InData)
{
	ObjectManager = ObjectManager::GetInstance();
	ObjectManager->Init();

	ImageInit();
	ObjectInit(InData);
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

	if (CurrentTime < 11.f)
	{
		CurrentTime += TimerManager::GetInstance()->GetDeltaTime();

		if (CurrentTime >= 11.f)
		{
			Fade* fadeOut = new Fade();
			fadeOut->Init(EFadeMode::FadeOut,ELevelState::Main);
			ObjectManager->AddObject(fadeOut, OBJ_UPPERUI);
		}
	}	
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
	ImageManager::GetInstance()->AddImage("record", L"Image/CupHead/UI/Screen/Win/record.bmp", 280, 63, 5, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("result_fx_puff", L"Image/CupHead/UI/Screen/Win/result_fx_puff.bmp", 7760, 359, 16, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("result_star", L"Image/CupHead/UI/Screen/Win/result_star.bmp", 12610, 359, 26, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("winscreen_circle", L"Image/CupHead/UI/Screen/Win/winscreen_circle.bmp", 984, 73, 12, 1, true, RGB(255, 0, 255));
}

void LevelResult::ObjectInit(void* InData)
{
	if (ObjectManager == nullptr)
		return;
	UIBackground* resultBackground = new UIBackground();
	resultBackground->Init("winscreen_bg");

	ObjectManager->AddObject(resultBackground, OBJ_UI);

	SimpleUI* result = new SimpleUI();
	result->Init("winscreen_results_title_a", 10.f, WINSIZE_X * 0.5f, 75.f);
	ObjectManager->AddObject(result, OBJ_UI);

	SimpleUI* cupHead = new SimpleUI();
	cupHead->Init("winscreen_ch", 20.f, WINSIZE_X * 0.25f, WINSIZE_Y * 0.5f,-1,true);
	ObjectManager->AddObject(cupHead, OBJ_UI);

	SimpleUI* board = new SimpleUI();
	board->Init("winscreen_board", 0.f, WINSIZE_X * 0.6f, WINSIZE_Y * 0.55f);
	ObjectManager->AddObject(board, OBJ_UI);

	if (InData != nullptr)
	{
		float RecordTime = 0.f;
		memcpy(&RecordTime, InData, sizeof(float));

		RecordUI* recordUI = new RecordUI();
		recordUI->Init("record", WINSIZE_X * 0.6f, WINSIZE_Y * 0.55f, RecordTime);
		ObjectManager->AddObject(recordUI, OBJ_UI);
	}

	Fade* fadeIn = new Fade();
	fadeIn->Init(EFadeMode::FadeIn);
	ObjectManager->AddObject(fadeIn, OBJ_UPPERUI);
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

#include "LevelLogo.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "LogoBackground.h"
#include "AlphaBackground.h"
#include "PotenUp.h"
#include "Image.h"
#include "LevelManager.h"

LevelLogo::LevelLogo()
	:ObjectManager(nullptr)
{
}

void LevelLogo::Init()
{
	ObjectManager = ObjectManager::GetInstance();
	ObjectManager->Init();

	ImageInit();
	ObjectInit();
}

void LevelLogo::Update()
{
	if (LevelManager::GetInstance()->GetNextLevelState() != LevelManager::GetInstance()->GetLevelState())
	{
		LevelManager::GetInstance()->SetLevelState(LevelManager::GetInstance()->GetNextLevelState());
		return;
	}

	if (ObjectManager != nullptr)
		ObjectManager->Update();
}

void LevelLogo::Render(HDC hdc)
{
	if (ObjectManager != nullptr)
		ObjectManager->RenderUI(hdc);
}

void LevelLogo::ImageInit()
{
	ImageManager::GetInstance()->AddImage("logobackground", L"Image/CupHead/UI/Screen/Logo/logobackground.bmp", 1280, 720, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("alphabackground", L"Image/CupHead/UI/Screen/Logo/alphabackground.bmp", 1280, 720, 1, 1, true, RGB(255, 0, 255));
	Image* potenupImage = ImageManager::GetInstance()->AddImage("potenup", L"Image/CupHead/UI/Screen/Logo/potenup.bmp", 1060, 176, 1, 1, true, RGB(255, 0, 255));
	if (potenupImage != nullptr)
		potenupImage->SetScale(0.5f, 0.5f);
}

void LevelLogo::ObjectInit()
{
	if (ObjectManager == nullptr)
		return;
	
	LogoBackground* logoBackground = new LogoBackground();
	logoBackground->Init();	
	ObjectManager->AddObject(logoBackground, OBJ_UI);

	for (int i = 1; i <= 3; ++i)
	{
		PotenUp* potenUp = new PotenUp();
		potenUp->Init(-(1060.f * 0.7f) * i);
		ObjectManager->AddObject(potenUp, OBJ_UI);
	}

	AlphaBackground* alphaBackground = new AlphaBackground();
	alphaBackground->Init(10.f);
	ObjectManager->AddObject(alphaBackground, OBJ_UI);
}

void LevelLogo::Release()
{
	if (ObjectManager != nullptr)
	{
		ObjectManager->Release();
		ObjectManager = nullptr;
	}
}

LevelLogo::~LevelLogo()
{
}

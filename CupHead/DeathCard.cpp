#include "DeathCard.h"
#include "Image.h"
#include "ImageManager.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "SimpleUI.h"
#include "Button.h"
#include "HildaBerg.h"

DeathCard::DeathCard()
	:bFirst(true), CurrentButtonIndex(0)
{
}

void DeathCard::Init(string InKey,float InX, float InY)
{
	pos.x = InX;
	pos.y = InY;

	image = ImageManager::GetInstance()->FindImage(InKey);
}

void DeathCard::Update()
{
	if (bFirst)
	{
		bFirst = false;
		DeathCardInit();
	}		

	if (!Buttons.empty())
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
			--CurrentButtonIndex;
		if(KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
			++CurrentButtonIndex;

		if (CurrentButtonIndex < 0)
			CurrentButtonIndex = 0;
		else if (CurrentButtonIndex >= Buttons.size())
			CurrentButtonIndex = Buttons.size() - 1;

		for (int i = 0; i < Buttons.size(); ++i)
			Buttons[i]->SetHover(false);
		
		Buttons[CurrentButtonIndex]->SetHover(true);
	}
}

void DeathCard::Render(HDC hdc)
{
	if (image != nullptr)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, CurFrameYIndex);
}

void DeathCard::DeathCardInit()
{
	void* Data =LevelManager::GetInstance()->GetData();
	if (Data)
	{
		FHildaBergData HilderBergData;
		ZeroMemory(&HilderBergData, sizeof(FHildaBergData));
		memcpy(&HilderBergData, Data, sizeof(FHildaBergData));

		SimpleUI* mugShot = new SimpleUI();
		mugShot->Init((HilderBergData.Phase < 5 ? "death_card_mugshot_blimp1" : "death_card_mugshot_moon"), 0.f, pos.x, pos.y - (image->GetFrameHeight() * 0.5f - 150.f));
		ObjectManager::GetInstance()->AddObject(mugShot, OBJ_UI);

		SimpleUI* text = new SimpleUI();
		text->Init((HilderBergData.Phase < 5 ? "DeathText1" : "DeathText3"), 0.f, pos.x, pos.y - (image->GetFrameHeight() * 0.5f - 300.f));
		ObjectManager::GetInstance()->AddObject(text, OBJ_UI);


		// 페이즈 개수 및 Hp로 비율 산정
		const float DefaultStartX = pos.x - image->GetFrameWidth() * 0.35f;
		const float DefaultEndX = image->GetFrameWidth() * 0.7f;
		int PhaseHp = 0;
		for (int i = 0; i < 5; ++i)
		{
			PhaseHp += HilderBergData.HpList[i];
			const float PhasePosX = DefaultStartX + DefaultEndX * (PhaseHp / (float)HilderBergData.TotalHp);
			SimpleUI* phaseIndex = new SimpleUI();
			phaseIndex->Init("phaseIndex", 0.f, PhasePosX, pos.y + (image->GetFrameWidth() * 0.09f));
			ObjectManager::GetInstance()->AddObject(phaseIndex, OBJ_UI);
		}		

		const float cupHeadPosX = DefaultStartX + DefaultEndX * ((float)(HilderBergData.TotalHp - HilderBergData.CurrentHp) / (float)HilderBergData.TotalHp);
		SimpleUI* cupHead = new SimpleUI();
		cupHead->Init("death_card_run", 15.f, cupHeadPosX, pos.y + (image->GetFrameWidth() * 0.075f));
		ObjectManager::GetInstance()->AddObject(cupHead, OBJ_UI);

		Button* Retry = new Button();
		Retry->Init("ReTry", pos.x, pos.y + image->GetFrameHeight() * 0.2f, EButtonType::ReTry);
		ObjectManager::GetInstance()->AddObject(Retry, OBJ_UI);

		Button* Exit = new Button();
		Exit->Init("Exit", pos.x, pos.y + image->GetFrameHeight() * 0.2f + 40.f, EButtonType::Exit);
		ObjectManager::GetInstance()->AddObject(Exit, OBJ_UI);
		Buttons.push_back(Retry);
		Buttons.push_back(Exit);
	}
}

void DeathCard::Release()
{
}

DeathCard::~DeathCard()
{
}
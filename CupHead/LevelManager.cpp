#include "LevelManager.h"
#include "LevelLogo.h"
#include "LevelMain.h"
#include "Level1.h"
#include "LevelResult.h"


void LevelManager::Init()
{
	LevelState = ELevelState::End;
	NextLevelState = ELevelState::End;
	Level = nullptr;
	Data = nullptr;
	SetLevelState(ELevelState::Logo);
}

void LevelManager::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown('1'))
		SetLevelState(ELevelState::Logo);
	if (KeyManager::GetInstance()->IsOnceKeyDown('2'))
		SetLevelState(ELevelState::Main);
	if (KeyManager::GetInstance()->IsOnceKeyDown('3'))
		SetLevelState(ELevelState::Level1);
	if (KeyManager::GetInstance()->IsOnceKeyDown('4'))
		SetLevelState(ELevelState::Result);

	Level->Update();
}

void LevelManager::Render(HDC hdc)
{
	Level->Render(hdc);
}

void LevelManager::SetLevelState(ELevelState InLevelState)
{
	if (LevelState == InLevelState)
		return;

	LevelState = InLevelState;
	NextLevelState = LevelState;

	if (Level != nullptr)
	{
		Level->Release();
		delete Level;
		Level = nullptr;
	}

	switch (LevelState)
	{
	case ELevelState::Logo:
		Level = new LevelLogo();
		break;
	case ELevelState::Main:
		Level = new LevelMain();
		break;
	case ELevelState::Level1:
		Level = new Level1();
		break;
	case ELevelState::Result:
		Level = new LevelResult();
		break;
	}

	Level->Init(Data);

	delete Data;
	Data = nullptr;
}

void LevelManager::SetNextLevelState(ELevelState InLevelState)
{
	NextLevelState = InLevelState;
}

void LevelManager::Release()
{
	if (Level != nullptr)
	{
		Level->Release();
		delete Level;
		Level = nullptr;
	}

	ReleaseInstance();
}
#pragma once
#include "Singleton.h"
#include "config.h"

enum class ELevelState : uint8_t
{
	Logo,
	Main,
	Level1,
	Result,
	End
};

class Level;
class LevelManager : public Singleton<LevelManager>
{
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void ReTry();

	ELevelState GetNextLevelState() const { return NextLevelState; }
	ELevelState GetLevelState() const { return LevelState; }
	void* GetData() const { return Data; }
	void SetLevelState(ELevelState InLevelState);
	void SetNextLevelState(ELevelState InLevelState) { NextLevelState = InLevelState; };
	void SetData(void* InData) { Data = InData; }
private:
	ELevelState NextLevelState;
	ELevelState LevelState;
	Level* Level;
	void* Data;
};


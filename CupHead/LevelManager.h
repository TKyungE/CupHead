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

	void SetLevelState(ELevelState InLevelState);

private:
	ELevelState LevelState;
	Level* Level;
};


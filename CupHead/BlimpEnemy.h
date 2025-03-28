#pragma once
#include "Character.h"
#include <unordered_map>

enum class BlimpEnemyState
{
	Idle,
	Attack,
	Turn,
	length
};

class Image;
class BlimpEnemy : public Character
{
public:
	BlimpEnemy();
	virtual ~BlimpEnemy();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	BlimpEnemyState CurState;
	unordered_map<BlimpEnemyState, pair<string, float>> AnimData;

};


#pragma once
#include "GameObject.h"
#include <vector>

class Enemy;
class EnemyManager : public GameObject
{
private: 
	Enemy* enemys;
	vector<Enemy*> vecEnemys;
	wchar_t szText[128];

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);
};


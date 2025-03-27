#pragma once
#include "GameObject.h"
#include <vector>

class Missile;
class MissileManager : public GameObject
{
private:
	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator iterMissiles;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};


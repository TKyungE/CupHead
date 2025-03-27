#include "MissileManager.h"
#include "Missile.h"

void MissileManager::Init()
{
	vecMissiles.resize(30);
	for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end(); iterMissiles++)
	{
		(*iterMissiles) = new Missile();
		(*iterMissiles)->Init();
	}
}

void MissileManager::Release()
{
}

void MissileManager::Update()
{
}

void MissileManager::Render(HDC hdc)
{
}

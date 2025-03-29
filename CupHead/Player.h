#pragma once
#include "GameObject.h"

class Image;
class LaughProjectile;
class StarProjectile;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init(FPOINT pos,FPOINT size);		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void EffectTestInit();
	//void EffectTest();

	//virtual void TakeDamage(float damage = 0.f);

private:
	Image* image;
	LaughProjectile* Laugh;
	StarProjectile* Star;
};


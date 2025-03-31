#pragma once
#include "Character.h"

class Image;

class Player : public Character
{
public:
	Player();
	~Player();

	void Init(FPOINT pos,FPOINT size);		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void EffectTestInit();
	void EffectTest();

	//virtual void TakeDamage(int damage = 0);

	void Move();

private:
	Image* image;
};


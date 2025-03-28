#pragma once
#include "GameObject.h"

class Image;
class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init(FPOINT pos,FPOINT size);		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	virtual void TakeDamage(float damage = 0.f);

private:
	Image* image;
};


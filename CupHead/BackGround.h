#pragma once
#include "GameObject.h"

class Image;
class BackGround : public GameObject
{
public:
	BackGround();
	virtual ~BackGround();

	void Init(FPOINT InPos, int InSpeed);		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);
private:
	Image* Image;
	int Speed;
};


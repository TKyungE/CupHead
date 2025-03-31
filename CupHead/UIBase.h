#pragma once
#include "Actor.h"

class UIBase : public Actor
{
public:
	UIBase();
	virtual ~UIBase();

	virtual void Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);
};


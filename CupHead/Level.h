#pragma once
#include "config.h"
class Level
{
public:
	Level() {};
	virtual ~Level() {};

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

protected:
	virtual void ImageInit() = 0; 
	virtual void ObjectInit() = 0;
};


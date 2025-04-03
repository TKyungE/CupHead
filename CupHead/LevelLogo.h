#pragma once
#include "Level.h"

class ObjectManager;
class LevelLogo : public Level
{
public:
	LevelLogo();
	virtual ~LevelLogo();

	virtual void Init(void* InData = nullptr) override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void ImageInit() override;
	virtual void ObjectInit(void* InData = nullptr) override;

private:
	ObjectManager* ObjectManager;
};


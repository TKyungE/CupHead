#pragma once
#include "Level.h"

class CollisionManager;
class ObjectManager;
class EffectManager;
class BackGroundManager;
class Level1 : public Level
{
public:
	Level1();
	virtual ~Level1();

	virtual void Init(void* InData = nullptr) override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void ImageInit() override;
	virtual void ObjectInit(void* InData = nullptr) override;

private:
	void TestCode();
private:
	BackGroundManager* BackgroundManager;
	CollisionManager* CollisionManager;
	ObjectManager* ObjectManager;
	EffectManager* EffectManager;

	float CurrentTime;
};


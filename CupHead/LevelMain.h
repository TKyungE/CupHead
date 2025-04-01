#pragma once
#include "Level.h"

class ObjectManager;
class LevelMain : public Level
{
public:
	LevelMain();
	virtual ~LevelMain();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void ImageInit() override;
	virtual void ObjectInit() override;

private:
	ObjectManager* ObjectManager;
};


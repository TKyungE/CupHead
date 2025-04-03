#pragma once
#include "Pawn.h"

namespace BulletInfo
{
	extern string imageTypes;
	extern int imageNum;
}

class Bullet : public Pawn
{
public:
	Bullet();
	virtual ~Bullet();

	void Init(FPOINT _pos, float _Angle);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

	// 나중에 옮기든지..
	float GetWidth();
	float GetHeight();

private:
	float Angle;
};


#pragma once
#include "Pawn.h"

namespace BulletInfo
{
	enum EBulletType
	{
		PLAYER,
		BLIMP_ENEMY,
		IMAGETYPE_END
	};

	extern string imageTypes[EBulletType::IMAGETYPE_END];
	extern int imageNum[EBulletType::IMAGETYPE_END];
}

class Bullet : public Pawn
{
public:
	Bullet();
	virtual ~Bullet();

	void Init(FPOINT _pos, float _Angle, BulletInfo::EBulletType imageType);
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


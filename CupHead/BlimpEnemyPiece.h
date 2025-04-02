#pragma once
#include "Pawn.h"

namespace BlimpEnemyPieceInfo
{
	enum EType
	{
		A,
		B,
		C,
		D,
		E,
		F,
		TYPE_END
	};

	extern string types[EType::TYPE_END];
}

class BlimpEnemyPiece : public Pawn
{
public:
	BlimpEnemyPiece(float Dx, float Dy);
	virtual ~BlimpEnemyPiece();

public:
	void Init(FPOINT _pos, BlimpEnemyPieceInfo::EType Type, string Color);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

private:
	void UpdateDy();

private:
	float Dx;
	float Dy;
};


#pragma once
#include "Pawn.h"
class BrokenPiece : public Pawn
{
public:
	BrokenPiece(float _Dx, float _Dy);
	virtual ~BrokenPiece();

public:
	void Init(FPOINT _pos, string ImageName);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Move() override;

private:
	void InitImage();
	void UpdateDy();

private:
	float Dx;
	float Dy;

};


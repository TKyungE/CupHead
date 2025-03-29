#include "Pawn.h"

Pawn::Pawn() : Speed(0.f)
{
}

Pawn::~Pawn()
{
}

void Pawn::Init()
{
}

void Pawn::Release()
{
}

void Pawn::Update()
{
	__super::Update();
}

void Pawn::Render(HDC hdc)
{
	__super::Render(hdc);
}

void Pawn::TakeDamage(int damage)
{
}

#include "Character.h"

Character::Character() :Hp(0), MaxHp(0)
{
}

Character::~Character()
{
}

void Character::Init()
{
}

void Character::Release()
{
}

void Character::Update()
{
	__super::Update();
}

void Character::Render(HDC hdc)
{
	__super::Render(hdc);
}

void Character::Move()
{
}

void Character::TakeDamage(int damage)
{
}

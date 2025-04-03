#include "Character.h"

Character::Character() :Hp(0), MaxHp(0), AlphaTime(0.f), MaxAlphaTime(0.f)
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

void Character::UpdateAlphaTime()
{
	AlphaTime -= TimerManager::GetInstance()->GetDeltaTime();
	AlphaTime = max(AlphaTime, 0.f);
}

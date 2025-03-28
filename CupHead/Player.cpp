#include "Player.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(FPOINT pos, FPOINT size)
{
	this->pos = pos;
	this->size = size;
	image = ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/Test/blimp_dash.bmp"), 21168, 415, 24, 1,
		true, RGB(255, 0, 255));

	// 콜라이더 삽입 방법				// Pivot = (이미지 가로 / 가로 프레임 수) / 2 , (이미지 세로 / 세로 프레임 수) / 2
	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { (21168 / 24) * 0.5f, 415 * 0.5f }, { 30.f,30.f }, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER);
}

void Player::Release()
{
}

void Player::Update()
{
	KeyManager* keyManager = KeyManager::GetInstance();
	if (keyManager)
	{
		FPOINT position = { 0.f,0.f };
		if (keyManager->IsStayKeyDown('W'))
			position.y = -1;

		else if (keyManager->IsStayKeyDown('S'))
			position.y = 1;

		if (keyManager->IsStayKeyDown('A'))
			position.x = -1;

		else if (keyManager->IsStayKeyDown('D'))
			position.x = 1;

		const float size = sqrtf(position.x * position.x + position.y * position.y);
		if (size)
		{
			position.x /= size;
			position.y /= size;
		}

		pos.x += position.x * 10 * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += position.y * 10 * TimerManager::GetInstance()->GetDeltaTime();
	}
}

void Player::Render(HDC hdc)
{
	if (image)
		image->Render(hdc,pos.x,pos.y,1);
}

void Player::TakeDamage(float damage)
{
}

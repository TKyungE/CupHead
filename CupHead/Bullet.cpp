#include "Bullet.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EffectManager.h"

namespace BulletInfo
{
	string imageTypes = { "BLIMP_ENEMY" };
	int imageNum = { 3 };
}

Bullet::Bullet()
	: Angle{}
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(FPOINT _pos, float _Angle)
{
#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
	// EnemyBullet
	string bulletType = BulletInfo::imageTypes;
	int imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		bulletType + to_string(imageNum),
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Bullet\\blimp_enemy_bullet_a.bmp"),
		368, 43,
		8, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		bulletType + to_string(imageNum),
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Bullet\\blimp_enemy_bullet_b.bmp"),
		264, 49,
		6, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		bulletType + to_string(imageNum),
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Bullet\\blimp_enemy_bullet_c.bmp"),
		470, 44,
		10, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region Effect Image Load
	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyBulletFx0",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Bullet\\blimp_enemy_bullet_fx_a.bmp"),
		1104, 107,
		12, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyBulletFx1",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Bullet\\blimp_enemy_bullet_fx_b.bmp"),
		1372, 94,
		14, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyBulletFx2",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Bullet\\blimp_enemy_bullet_fx_c.bmp"),
		1100, 98,
		11, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	Angle = _Angle;

	int randomImageNum = uid(dre) % BulletInfo::imageNum;
	string imageStr = BulletInfo::imageTypes + to_string(randomImageNum);
	image = ImageManager::GetInstance()->FindImage(imageStr);

	CurFrameIndex = 0;
	FrameSpeed = 10.f;
	FrameTime = 0.f;

	Speed = 450.f;
	IsFlip = false;
	pos = _pos;
	size = { 1.f,1.f };
	bDead = false;

	float sizeX = GetWidth();
	float sizeY = GetHeight();
	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { sizeX * 0.5f, sizeY * 0.5f }, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER_WEAPON);

	EffectManager::GetInstance()->AddEffect("BlimpEnemyBulletFx" + to_string(randomImageNum), pos, 1.f);
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	Move();
	UpdateFrame();

	if (OutOfScreen(pos, GetWidth(), GetHeight()))
	{
		bDead = true;
	}
}

void Bullet::Render(HDC hdc)
{
	if (image)
	{
		image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, false);
	}
}

void Bullet::Move()
{
	pos.x += Speed * TimerManager::GetInstance()->GetDeltaTime()
		* cosf((float)DEG_TO_RAD(Angle));
	pos.y -= Speed * TimerManager::GetInstance()->GetDeltaTime()
		* sinf((float)DEG_TO_RAD(Angle));
}

float Bullet::GetWidth()
{
	if (image)
	{
		return (float)image->GetFrameWidth();
	}
	return 0.0f;
}

float Bullet::GetHeight()
{
	if (image)
	{
		return (float)image->GetFrameHeight();
	}
	return 0.0f;
}

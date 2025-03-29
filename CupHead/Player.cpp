#include "Player.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "LaughProjectile.h"
#include "StarProjectile.h"
#include "EffectManager.h"

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
	image = nullptr;
	/*image = ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/Test/blimp_dash.bmp"), 21168, 415, 24, 1,
		true, RGB(255, 0, 255));*/

	// �ݶ��̴� ���� ���				// Pivot = (�̹��� ���� / ���� ������ ��) / 2 , (�̹��� ���� / ���� ������ ��) / 2
	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, {0.f,0.f}/*{ (21168 / 24) * 0.5f, 415 * 0.5f }*/, { 30.f,30.f }, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER);

	EffectTestInit();

	Laugh = new LaughProjectile();
	Laugh->Init();

	Star = new StarProjectile();
	Star->Init();

	


}

void Player::Release()
{
	if (Laugh)
	{
		Laugh->Release();
		delete Laugh;
		Laugh = nullptr;
	}

	if (Star)
	{
		Star->Release();
		delete Star;
		Star = nullptr;
	}
}

void Player::Update()
{
	Laugh->Update();
	Star->Update();
	EffectTest();
	KeyManager* keyManager = KeyManager::GetInstance();
	if (keyManager)
	{
		FPOINT position = { 0.f,0.f };

		
		if (keyManager->IsOnceKeyDown('Q'))
		{
			//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
			//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
			EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f);
			EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f);
			EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f);
		}

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

		pos.x += position.x * 300 * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += position.y * 300 * TimerManager::GetInstance()->GetDeltaTime();
	}
}

void Player::Render(HDC hdc)
{
	if (image)
		image->Render(hdc,pos.x,pos.y,1);

	//Laugh->Render(hdc);
	Star->Render(hdc);
}

void Player::EffectTestInit()
{
	//C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\Hilda Berg\Enemy\Explode
	ImageManager::GetInstance()->AddImage("blimp_enemy_explode", TEXT("Image/CupHead/Hilda Berg/Enemy/Explode/blimp_enemy_explode.bmp"), 4172, 217, 14, 1, true, RGB(255, 0, 255)); // ����Ʈ �׽�Ʈ
	ImageManager::GetInstance()->AddImage("blimp_enemy_spark", TEXT("Image/CupHead/Hilda Berg/Enemy/Explode/blimp_enemy_spark.bmp"), 2232, 260, 9, 1, true, RGB(255, 0, 255)); // ����Ʈ �׽�Ʈ

	//C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\Hilda Berg\Moon\Attack
	ImageManager::GetInstance()->AddImage("blimp_star_fx", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_fx.bmp"), 1120, 70, 8, 1, true, RGB(255, 0, 255)); // ����Ʈ �׽�Ʈ

	// C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\Hilda Berg\Sagittarius\Arrow\Smoke
	ImageManager::GetInstance()->AddImage("sagg_arrow_fx", TEXT("Image/CupHead/Hilda Berg/Sagittarius/Arrow/Smoke/sagg_arrow_fx.bmp"), 1045, 203, 5, 1, true, RGB(255, 0, 255)); // ����Ʈ �׽�Ʈ
}

void Player::EffectTest()
{
	KeyManager* keyManager = KeyManager::GetInstance();

	if (keyManager->IsOnceKeyDown('Q')) // Default Test
	{
		EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f); // 1�ʵ��� �� �� �����ְ� �������
	}

	if (keyManager->IsOnceKeyDown('W')) // OffsetPos Test
	{
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f, { -100.f,-100.f }); // 0.5�� ���� �� �� �����ִµ� pos + offset ��ġ�� ����
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f, { -100.f, +100.f }); // 0.5�� ���� �� �� �����ִµ� pos + offset ��ġ�� ����
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f, { +100.f, -100.f }); // 0.5�� ���� �� �� �����ִµ� pos + offset ��ġ�� ����
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f, { +100.f, +100.f }); // 0.5�� ���� �� �� �����ִµ� pos + offset ��ġ�� ����
	}

	if (keyManager->IsOnceKeyDown('E')) // MaxLoopTest
	{
		EffectManager::GetInstance()->AddEffect("sagg_arrow_fx", pos, 3.f, { 0.f, 0.f }, 5); // MaxLoopTest, 3�ʵ��� 5�� ���� �� ����
	}

	if (keyManager->IsOnceKeyDown('R')) // TraceTest 
	{
		EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 10.f , { 0.f, 0.f }, 30, true, this); // Trace�� �Ǵµ� �����غ��� ���� ����� ���� �ʿ�.
	}

	if (keyManager->IsOnceKeyDown('T'))
	{
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f);
		EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 0.5f);
	}

	if (keyManager->IsOnceKeyDown('Y'))
	{
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f);
		EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 0.5f);
	}

	if (keyManager->IsOnceKeyDown('U'))
	{
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
		//EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 3.f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_explode", pos, 1.f);
		EffectManager::GetInstance()->AddEffect("blimp_enemy_spark", pos, 0.5f);
		EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 0.5f);
	}
}

void Player::TakeDamage(float damage)
{
}

#include "Sagittarius.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "SagittariusArrow.h"
#include "SagittariusStar.h"
#include "ObjectManager.h"
#include "SagittariusCloud.h"
#include "SagittariusStar2.h"

Sagittarius::Sagittarius()
	:Angle(0.f), AngleSpeed(0.f), CurrnetTime(0.f), AttackTime(0.f), bAttack(false), Cloud(nullptr)
{
}

void Sagittarius::Init(FPOINT InPos, float InAngle, int _Hp)
{
	// Test. HildaBerg Change Form
	Hp = _Hp;

	State = ESagittariusState::Idle;
	pos = InPos;
	Angle = InAngle;
	Speed = 150.f;
	FrameSpeed = 10.f;
	AngleSpeed = 250.f;
	AttackTime = 5.f;

	image = ImageManager::GetInstance()->AddImage("sagg_idle", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Idle/sagg_idle.bmp", 5580, 362, 12, 1, true, RGB(255, 0, 255));

	MaxAlphaTime = 0.1f;

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { (float)image->GetFrameWidth(), (float)image->GetFrameHeight() }, true, MaxAlphaTime);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJ_MONSTER);

	Cloud = new SagittariusCloud();
	Cloud->Init(this, { image->GetFrameWidth() * 0.35f, image->GetFrameHeight() * 0.5f });
	ObjectManager::GetInstance()->AddObject(Cloud, OBJ_MONSTER_WEAPON);
}


void Sagittarius::Update()
{
	UpdateAlphaTime();

	switch (State)
	{
	case Sagittarius::ESagittariusState::Idle:
		Idle();
		break;
	case Sagittarius::ESagittariusState::Attack:
		Attack();
		break;
	case Sagittarius::ESagittariusState::End:
		break;
	default:
		break;
	}

	UpdateFrame();

	Move();

	if (bDead && Cloud != nullptr)
		Cloud->SetDead(true);
}

void Sagittarius::Render(HDC hdc)
{
	//if (image)
	//{
	//	image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0);

	//	// ���ʹ� ���� �� ��� ���̴µ� �÷��̾�� ������ ���ĺ������� �׷����� bool ���ڷ� �б��߽��ϴ�.
	//	//image->FrameRenderAlpha(hdc, pos.x, pos.y, CurFrameIndex, 0, true, 85, RGB(255, 255, 255)); // true�� ����FrameRender�ϰ� �� ���� ���ϴ� �÷����� AlphaValue����ŭ AlphaBlend�ؼ� �׸��� �Լ�.
	//	//image->FrameRenderAlpha(hdc, pos.x, pos.y, CurFrameIndex, 0, false, 85); // false�� ���� �̹����� AlphaValue����ŭ AlphaBlend�ؼ� �׸��� �Լ�.
	//}

	if (image)
	{
		if (0.f < AlphaTime)
		{
			image->FrameRenderAlpha(hdc, pos.x, pos.y, CurFrameIndex, 0, false, 135, RGB(255, 255, 255),IsFlip);
		}

		else
		{
			image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, IsFlip);
			AlphaTime = 0.f;
		}
	}
}

void Sagittarius::Move()
{
	Angle += AngleSpeed * TimerManager::GetInstance()->GetDeltaTime();

	pos.x += Speed * cosf(DEG_TO_RAD(Angle)) * TimerManager::GetInstance()->GetDeltaTime();
	pos.y -= Speed * sinf(DEG_TO_RAD(Angle * 0.5f)) * TimerManager::GetInstance()->GetDeltaTime();
}

void Sagittarius::TakeDamage(int damage)
{
	// Test. HildaBerg Change Form
	Hp -= damage;
	AlphaTime = MaxAlphaTime;
	if (Hp <= 0) bDead = true;
}

void Sagittarius::Idle()
{
	CurrnetTime += TimerManager::GetInstance()->GetDeltaTime();
	if (CurrnetTime >= AttackTime)
	{
		FrameTime = 0.f;
		CurFrameIndex = 0;
		IsStayMaxFrame = true;

		CurrnetTime = 0.f;
		State = ESagittariusState::Attack;

		image = ImageManager::GetInstance()->AddImage("sagg_attack", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Attack/sagg_attack.bmp", 6496, 344, 14, 1, true, RGB(255, 0, 255));
	}
}

void Sagittarius::Attack()
{
	if (!bAttack && CurFrameIndex >= 6)
	{
		bAttack = true;

		FPOINT StarPos = { pos.x - image->GetFrameHeight() * 0.5f, pos.y - 40.f };
		FPOINT ArrowPos = { pos.x, pos.y - 40.f };

		SagittariusStar* star = new SagittariusStar(StarPos, 10.f, 180.f);
		star->Init();
		ObjectManager::GetInstance()->AddObject(star, OBJTYPE::OBJ_MONSTER_WEAPON);

		SagittariusStar* star1 = new SagittariusStar(StarPos, 10.f, 125.f);
		star1->Init();
		ObjectManager::GetInstance()->AddObject(star1, OBJTYPE::OBJ_MONSTER_WEAPON);

		SagittariusStar* star2 = new SagittariusStar(StarPos, 10.f, 225.f);
		star2->Init();
		ObjectManager::GetInstance()->AddObject(star2, OBJTYPE::OBJ_MONSTER_WEAPON);

		SagittariusArrow* arrow = new SagittariusArrow(ArrowPos, { 50.f,50.f });
		arrow->Init();
		ObjectManager::GetInstance()->AddObject(arrow, OBJTYPE::OBJ_MONSTER_WEAPON);


		for (int i = 0; i < WINSIZE_Y / 90.f; ++i)
		{
			SagittariusStar2* sagittariusStar2 = new SagittariusStar2();
			sagittariusStar2->Init("sagg_star", WINSIZE_X, i * 90.f, 400.f);
			ObjectManager::GetInstance()->AddObject(sagittariusStar2, OBJTYPE::OBJ_MONSTER_WEAPON);
		}

	}
	else if (bAttack && CurFrameIndex == image->GetMaxFrameX() - 1)
	{
		FrameTime = 0.f;
		CurFrameIndex = 0;
		IsStayMaxFrame = false;

		bAttack = false;
		State = ESagittariusState::Idle;

		image = ImageManager::GetInstance()->AddImage("sagg_idle", L"Image/CupHead/Hilda Berg/Sagittarius/Sagittarius/Idle/sagg_idle.bmp", 5580, 362, 12, 1, true, RGB(255, 0, 255));
	}
}

void Sagittarius::Release()
{
}
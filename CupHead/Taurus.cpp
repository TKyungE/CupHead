#include "Taurus.h"
#include "Image.h"
#include "BarrageBullet.h"

#include "CommonFunction.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "CollisionManager.h"

namespace TaurusInfo
{
	string states[EState::STATE_END] = {
		"TAURUS_IDLE",
		"TAURUS_ATTACK" };
}

Taurus::Taurus()
	: Angle{}, AngleSpeed{},
	CurState{}, AnimData{}, IsAnimEnd{},
	ElapsedAttackTime{}, AttackCoolTime{ 5.f },
	PosBefore{},
	AttackCollider{},
	ElapsedBarrageTime{}, BarrageCoolTime{ 0.2f }
{
}

Taurus::~Taurus()
{
}

void Taurus::Init(FPOINT _Pos, float _Angle, int _Hp)
{
#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
	string stateStr = TaurusInfo::states[TaurusInfo::EState::IDLE];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Taurus\\taurus_idle.bmp"),
		8544, 471,
		16, 1,
		true, RGB(255, 0, 255));

	stateStr = TaurusInfo::states[TaurusInfo::EState::ATTACK];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Taurus\\taurus_attack.bmp"),
		24339, 448,
		21, 1,
		true, RGB(255, 0, 255));

#pragma endregion

	CurState = TaurusInfo::EState::STATE_END;

	for (int state = 0; state < TaurusInfo::EState::STATE_END; ++state)
	{
		AnimData.push_back({ TaurusInfo::states[state], 15.f });
	}

	SetState(TaurusInfo::EState::IDLE);

	float sizeX = GetWidth();
	float sizeY = GetHeight();

	Speed = 150.f;
	AngleSpeed = 250.f;
	IsFlip = false;
	pos = _Pos;
	Angle = _Angle;
	size = { 1.f,1.f };
	bDead = false;

	Hp = _Hp;

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f, -20.f }, { sizeX * 0.7f, sizeY * 0.5f }, true, 0.1f);
	collider->Init();
	AttackCollider = collider;
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER);
}

void Taurus::Release()
{
}

void Taurus::Update()
{
	UpdateFrame();

	UpdateState();
}

void Taurus::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, IsFlip);
}

void Taurus::UpdateFrame()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();

	int tempIndex = CurFrameIndex;
	int maxFrame = 1;
	if (image)
		maxFrame = image->GetMaxFrameX() * image->GetMaxFrameY();

	CurFrameIndex = (int)FrameTime % maxFrame;

	// IsAnimEnd
	if (CurFrameIndex < tempIndex)
	{
		if (true == IsStayMaxFrame)
		{
			CurFrameIndex = maxFrame - 1;
		}

		else
		{
			IsAnimEnd = true;
		}
	}
}

void Taurus::Move()
{
	Angle += AngleSpeed * TimerManager::GetInstance()->GetDeltaTime();

	pos.x += Speed * cosf(DEG_TO_RAD(Angle)) * TimerManager::GetInstance()->GetDeltaTime();
	pos.y -= Speed * sinf(DEG_TO_RAD(Angle * 0.5f)) * TimerManager::GetInstance()->GetDeltaTime();
}

void Taurus::TakeDamage(int damage)
{
	if (Hp <= 0) return;
	Hp -= damage;
}

void Taurus::UpdateState()
{
	switch (CurState)
	{
	case TaurusInfo::EState::IDLE:
	{
		if (Hp <= 0)
		{
			// after finish attack
			bDead = true;

		}

		Move();

		ElapsedAttackTime += TimerManager::GetInstance()->GetDeltaTime();
		if (ElapsedAttackTime >= AttackCoolTime)
		{
			ElapsedAttackTime = 0.f;
			PosBefore = pos;
			SetState(TaurusInfo::EState::ATTACK);
		}
		break;
	}
	case TaurusInfo::EState::ATTACK:
	{
		float sizeX = GetWidth();
		float sizeY = GetHeight();
		if (CurFrameIndex >= 11 and CurFrameIndex <= 13 )
		{
			AttackCollider->SetSize({ sizeX, sizeY * 0.5f });
			AnimData[TaurusInfo::EState::ATTACK].second = 20.f;
			Speed = 600;
			Dash();
		}
		else if (CurFrameIndex >= 18)
		{
			AnimData[TaurusInfo::EState::ATTACK].second = 5.f;
			Speed = 150;
			Recover();
		}


		if (IsAnimEnd)
		{
			Speed = 150;
			AnimData[TaurusInfo::EState::ATTACK].second = 15.f;
			pos = PosBefore;
			SetState(TaurusInfo::EState::IDLE);

			sizeX = GetWidth();
			sizeY = GetHeight();
			AttackCollider->SetSize({ sizeX * 0.7f, sizeY * 0.5f });
		}

		ElapsedBarrageTime += TimerManager::GetInstance()->GetDeltaTime();
		if (ElapsedBarrageTime >= BarrageCoolTime)
		{
			ElapsedBarrageTime = 0.f;
			BarrageFire();
		}
		break;
	}
	}
}

void Taurus::SetState(TaurusInfo::EState NewState)
{
	if (CurState == NewState) return;

	CurState = NewState;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first);
	int maxFrame{ 1 };
	if (image)
	{
		maxFrame = image->GetMaxFrameX() * image->GetMaxFrameY();
	}
	CurFrameIndex = 0;
	FrameSpeed = AnimData[CurState].second;
	FrameTime = 0.f;
	IsAnimEnd = false;
}

void Taurus::Dash()
{
	pos.x -= Speed * 5.f * TimerManager::GetInstance()->GetDeltaTime();
}

void Taurus::Recover()
{
	float deltaX = PosBefore.x - pos.x;
	pos.x += (Speed * 0.5f * deltaX * TimerManager::GetInstance()->GetDeltaTime()) / (float)(image->GetMaxFrameX() - CurFrameIndex);
}

void Taurus::BarrageFire()
{
	FPOINT bulletPos{ (float)WINSIZE_X, pos.y };
	float bulletAngle{ 100.f };
	for (int j = 0; j < 10; ++j) {
		bulletAngle += j * 4;
		BarrageBullet* bullet = new BarrageBullet();
		bullet->Init(bulletPos, bulletAngle, 50, 20.f);
		ObjectManager::GetInstance()->AddObject(bullet, OBJ_MONSTER_WEAPON);
	}
}

float Taurus::GetWidth()
{
	if (image)
	{
		return (float)image->GetFrameWidth();
	}
}

float Taurus::GetHeight()
{
	if (image)
	{
		return (float)image->GetFrameHeight();
	}
}

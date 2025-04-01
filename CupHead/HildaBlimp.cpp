#include "HildaBlimp.h"
#include "Image.h"
#include "LaughProjectile.h"
#include "Tornado.h"

#include "CommonFunction.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "CollisionManager.h"

namespace HildaBlimpInfo
{
	string states[EState::STATE_END] = {
		"INTRO",
		"IDLE",
		"SHOOT",
		"TORNADO",
		"DASH",
		"SUMMON",
		"SUMMONRECOVER",
		"MORPH1",
		"MORPH2",
		"MORPH3",
		"MORPH4"
	};
}

HildaBlimp::HildaBlimp(int _Phase)
	: Phase{ _Phase },
	Angle{}, AngleSpeed{},
	CurState{}, AnimData{}, IsAnimEnd{},
	ElapsedShootTime{}, ShootCoolTime{ 7.f },
	HaShootCnt{}, HaMaxShootCnt{ 1 },
	ElapsedAnimTime{}
{
}

HildaBlimp::~HildaBlimp()
{
}

void HildaBlimp::Init(FPOINT _Pos, float _Angle)
{
#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
	string stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::INTRO];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_intro.bmp"),
		20554, 461,
		43, 1,
		true, RGB(255, 0, 255));
	
	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::IDLE];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_idle.bmp"),
		7539, 393,
		21, 1,
		true, RGB(255, 0, 255));
	
	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::SHOOT];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_shoot.bmp"),
		6745, 397,
		19, 1,
		true, RGB(255, 0, 255));
	
	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::TORNADO];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_tornado.bmp"),
		19152, 507,
		38, 1,
		true, RGB(255, 0, 255));
	
	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::DASH];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_dash.bmp"),
		21168, 415,
		24, 1,
		true, RGB(255, 0, 255));
	
	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::SUMMON];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_summon.bmp"),
		5355, 433,
		15, 1,
		true, RGB(255, 0, 255));

	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::SUMMONRECOVER];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\blimp_summon_recover.bmp"),
		2346, 419,
		6, 1,
		true, RGB(255, 0, 255));

	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::MORPH1];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Trans\\blimp_morph_1.bmp"),
		2793, 399,
		7, 1,
		true, RGB(255, 0, 255));

	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::MORPH2];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Trans\\blimp_morph_2.bmp"),
		4062, 424,
		6, 1,
		true, RGB(255, 0, 255));

	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::MORPH3];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Trans\\blimp_morph_3.bmp"),
		18425, 510,
		25, 1,
		true, RGB(255, 0, 255));

	stateStr = HildaBlimpInfo::states[HildaBlimpInfo::EState::MORPH4];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Trans\\blimp_morph_4.bmp"),
		9490, 801,
		10, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	CurState = HildaBlimpInfo::EState::STATE_END;

	for (int state = 0; state < HildaBlimpInfo::EState::STATE_END; ++state)
	{
		AnimData.push_back({ HildaBlimpInfo::states[state], 15.f });
	}

	SetState(HildaBlimpInfo::EState::INTRO);

	if (Phase > 0)
	{
		FrameTime = CurFrameIndex = 37;
	}

	float sizeX = GetWidth();
	float sizeY = GetHeight();

	Speed = 150.f;
	AngleSpeed = 250.f;
	IsFlip = false;
	pos = _Pos;
	Angle = _Angle;
	size = { 1.f,1.f };
	bDead = false;

	Hp = 50;

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { sizeX * 0.5f, sizeY * 0.5f }, true, 0.1f);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER);
}

void HildaBlimp::Release()
{
}

void HildaBlimp::Update()
{
	UpdateState();

	UpdateFrame();
}

void HildaBlimp::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, IsFlip);
}

void HildaBlimp::UpdateFrame()
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

void HildaBlimp::Move()
{
	Angle += AngleSpeed * TimerManager::GetInstance()->GetDeltaTime();

	pos.x += Speed * cosf(DEG_TO_RAD(Angle)) * TimerManager::GetInstance()->GetDeltaTime();
	pos.y -= Speed * sinf(DEG_TO_RAD(Angle * 0.5f)) * TimerManager::GetInstance()->GetDeltaTime();
}

void HildaBlimp::TakeDamage(int damage)
{
	Hp -= damage;
}

void HildaBlimp::UpdateState()
{
	switch (CurState)
	{
	case HildaBlimpInfo::EState::INTRO:
	{
		if (IsAnimEnd)
		{
			SetState(HildaBlimpInfo::EState::IDLE);
		}
		break;
	}
	case HildaBlimpInfo::EState::IDLE:
	{
		if (Hp <= 0)
		{
			if (Phase != 2)
			{
				SetState(HildaBlimpInfo::EState::DASH);
			}
			else
			{
				SetState(HildaBlimpInfo::EState::MORPH1);
			}
			return;
		}

		Move();

		ElapsedShootTime += TimerManager::GetInstance()->GetDeltaTime();
		if (ElapsedShootTime >= ShootCoolTime)
		{
			ShootPaternByPhase();
		}
		break;
	}
	case HildaBlimpInfo::EState::SHOOT:
	{
		if (CurFrameIndex >= 5)
		{
			ShootHa();
			ElapsedShootTime = 0.f;
		}

		if (IsAnimEnd)
		{
			SetState(HildaBlimpInfo::EState::IDLE);
		}
		break;
	}
	case HildaBlimpInfo::EState::TORNADO:
	{
		ShootTornado();
		ElapsedShootTime = 0.f;

		if (IsAnimEnd)
		{
			SetState(HildaBlimpInfo::EState::IDLE);
		}
		break;
	}
	case HildaBlimpInfo::EState::DASH:
	{
		if (CurFrameIndex >= 18)
		{
			Dash();
		}
		if (IsAnimEnd)
		{
			FrameTime = CurFrameIndex = 21;
			IsAnimEnd = false;
		}
		if (pos.x <= -GetWidth()/2.f)
		{
			SetState(HildaBlimpInfo::EState::SUMMON);
		}
		break;
	}
	case HildaBlimpInfo::EState::SUMMON:
	{
		DashRecover();
		if (pos.x > WINSIZE_X - 200.f)
		{
			SetState(HildaBlimpInfo::EState::SUMMONRECOVER);
		}
		break;
	}
	case HildaBlimpInfo::EState::SUMMONRECOVER:
	{
		if (IsAnimEnd)
		{
			bDead = true;
		}
		break;
	}
	case HildaBlimpInfo::EState::MORPH1:
	{
		ElapsedAnimTime += TimerManager::GetInstance()->GetDeltaTime();
		if (IsAnimEnd)
		{
			if (ElapsedAnimTime > 5.f)
			{
				SetState(HildaBlimpInfo::EState::MORPH2);
				ElapsedAnimTime = 0.f;
			}
			else
			{
				FrameTime = CurFrameIndex = 1;
				IsAnimEnd = false;
			}
		}
		break;
	}
	case HildaBlimpInfo::EState::MORPH2:
	{
		IsAnimEnd = false;
		ElapsedAnimTime += TimerManager::GetInstance()->GetDeltaTime();

		if (ElapsedAnimTime > 2.f)
		{
			SetState(HildaBlimpInfo::EState::MORPH3);
			ElapsedAnimTime = 0.f;
		}
		break;
	}
	case HildaBlimpInfo::EState::MORPH3:
	{
		if (IsAnimEnd)
		{
			SetState(HildaBlimpInfo::EState::MORPH4);
		}
		break;
	}
	case HildaBlimpInfo::EState::MORPH4:
	{
		float deltaX = (WINSIZE_X - 310.f) - pos.x;
		float deltaY = (WINSIZE_Y * 0.5f) - pos.y;
		pos.x += deltaX * 5.f * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += deltaY * 5.f * TimerManager::GetInstance()->GetDeltaTime();

		if (IsAnimEnd)
		{
			FrameTime = CurFrameIndex = 19;
			IsAnimEnd = false;
		}

		if (GetDistance({ 0,0 }, { deltaX, deltaY }) <= 1.f)
		{
			bDead = true;
		}
		break;
	}
	}
}

void HildaBlimp::SetState(HildaBlimpInfo::EState NewState)
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

void HildaBlimp::ShootPaternByPhase()
{
	if (HaShootCnt < HaMaxShootCnt)
	{
		SetState(HildaBlimpInfo::EState::SHOOT);

		if (Phase != 0)
		{
			HaShootCnt++;
		}
	}
	else
	{
		SetState(HildaBlimpInfo::EState::TORNADO);

		HaShootCnt = 0;
		switch (Phase)
		{
		case 1:
		{
			if (HaMaxShootCnt == 2) HaMaxShootCnt = 3;
			else if (HaMaxShootCnt == 3) HaMaxShootCnt = 2;
			break;
		}
		case 2:
		{
			if (HaMaxShootCnt == 1) HaMaxShootCnt = 2;
			else if (HaMaxShootCnt == 2) HaMaxShootCnt = 1;
			break;
		}
		}
	}
}

void HildaBlimp::ShootHa()
{
	if (ElapsedShootTime < ShootCoolTime) return;

	LaughProjectile* ha = new LaughProjectile;
	ha->Init(pos);
	ObjectManager::GetInstance()->AddObject(ha, OBJ_MONSTER_WEAPON);
}

void HildaBlimp::ShootTornado()
{
	if (ElapsedShootTime < ShootCoolTime) return;

	Tornado* tornado = new Tornado;
	tornado->Init({ pos.x-GetWidth()/2.f, pos.y});
	ObjectManager::GetInstance()->AddObject(tornado, OBJ_MONSTER_WEAPON);
}

void HildaBlimp::Dash()
{
	pos.x -= Speed * 10.f * TimerManager::GetInstance()->GetDeltaTime();
}

void HildaBlimp::DashRecover()
{
	pos.x += Speed * 3.f * TimerManager::GetInstance()->GetDeltaTime();
}

float HildaBlimp::GetWidth()
{
	if (image)
	{
		return (float)image->GetFrameWidth();
	}
	return 0.0f;
}

float HildaBlimp::GetHeight()
{
	if (image)
	{
		return (float)image->GetFrameHeight();
	}
	return 0.0f;
}
#include "Tornado.h"
#include "Image.h"
#include "CommonFunction.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "CollisionManager.h"

namespace TornadoInfo
{
	string states[EState::STATE_END] = { "TornadoIntro", "TornadoAttack" };
}

Tornado::Tornado()
	:Dx{}, Angle{ 180.f }, MaxChaseDistance{ 150.f },
	CurState{ TornadoInfo::EState::INTRO }, AnimData{}, IsAnimEnd{}, IsAnimReverse{}
{
}

Tornado::~Tornado()
{
}

void Tornado::Init(FPOINT _pos)
{

#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
	// GreenEnemy
	string stateStr = TornadoInfo::states[TornadoInfo::EState::INTRO];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\Attack\\tornado_intro.bmp"),
		2604, 687,
		12, 1,
		true, RGB(255, 0, 255));

	stateStr = TornadoInfo::states[TornadoInfo::EState::ATTACK];
	ImageManager::GetInstance()->AddImage(
		stateStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Normal\\Attack\\tornado_attack.bmp"),
		5536, 350,
		16, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	CurState = TornadoInfo::EState::STATE_END;

	// 일단 애니메이션 속도 전부 10.f
	for (int state = 0; state < TornadoInfo::EState::STATE_END; ++state)
	{
		AnimData.push_back({ TornadoInfo::states[state], 10.f });
	}

	SetState(TornadoInfo::EState::INTRO, false);

	Speed = 250.f;
	IsFlip = false;
	pos = _pos;
	size = { 1.f,1.f };
	bDead = false;
}

void Tornado::Release()
{
}

void Tornado::Update()
{
	UpdateState();

	UpdateFrame();
}

void Tornado::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, IsFlip);
}

void Tornado::UpdateFrame()
{
	FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();

	int tempIndex = CurFrameIndex;
	int maxFrame = 1;
	if (image)
		maxFrame = image->GetMaxFrameX() * image->GetMaxFrameY();

	if (IsAnimReverse)
	{
		CurFrameIndex = maxFrame - (int)FrameTime % maxFrame;
	}
	else
	{
		CurFrameIndex = (int)FrameTime % maxFrame;
	}

	// IsAnimEnd
	if ((!IsAnimReverse and CurFrameIndex < tempIndex) or
		(IsAnimReverse and CurFrameIndex > tempIndex))
	{
		if (true == IsStayMaxFrame)
		{
			CurFrameIndex = IsAnimReverse ? 0 : maxFrame - 1;
		}

		else
		{
			IsAnimEnd = true;
		}
	}
}

void Tornado::Move()
{
	pos.x += Dx * Speed * TimerManager::GetInstance()->GetDeltaTime();
	pos.y -= Speed * TimerManager::GetInstance()->GetDeltaTime()
		* sinf((float)DEG_TO_RAD(Angle));
}

void Tornado::UpdateState()
{
	switch (CurState)
	{
	case TornadoInfo::EState::INTRO:
	{
		INTRO();
		break;
	}
	case TornadoInfo::EState::ATTACK:
	{
		ATTACK();
		break;
	}
	}
}

void Tornado::INTRO()
{
	if (IsAnimEnd)
	{
		SetState(TornadoInfo::EState::ATTACK, false);

		float sizeX = GetWidth();
		float sizeY = GetHeight();

		Collider* collider1 = new Collider(this, COLLIDERTYPE::Rect, { 0.f,-sizeY * 0.2f }, { sizeX * 0.7f, sizeY * 0.5f }, true);
		collider1->Init();
		CollisionManager::GetInstance()->AddCollider(collider1, OBJTYPE::OBJ_MONSTER_WEAPON);

		Collider* collider2 = new Collider(this, COLLIDERTYPE::Rect, { 0.f, sizeY * 0.25f }, { sizeX * 0.3f, sizeY * 0.4f }, true);
		collider2->Init();
		CollisionManager::GetInstance()->AddCollider(collider2, OBJTYPE::OBJ_MONSTER_WEAPON);
	}
}

void Tornado::ATTACK()
{
	Dx += -1.f * TimerManager::GetInstance()->GetDeltaTime();
	Dx = ClampValue(Dx, -1.f, 0.f);

	if (OutOfScreen(pos, GetWidth(), GetHeight()))
	{
		bDead = true;
	}
	else
	{
		GameObject* target{};
		list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJTYPE::OBJ_PLAYER);
		if (!playerList.empty())
		{
			target = playerList.front();
		}

		if (target)
		{
			if (pos.x - GetWidth() / 2 > target->GetPos().x + MaxChaseDistance)
			{
				float deltaAngle = (float)RAD_TO_DEG(GetAngle(pos, target->GetPos()));
				// [-180, 180] -> [0, 360]
				deltaAngle = fmod((deltaAngle + 360.f), 360.f);

				Angle = Lerp(deltaAngle, Angle, 0.6f);
			}
		}
	}

	Move();
}

void Tornado::SetState(TornadoInfo::EState NewState, bool AnimReverse)
{
	if ((CurState == NewState) and (IsAnimReverse == AnimReverse)) return;

	CurState = NewState;
	IsAnimReverse = AnimReverse;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first);
	int maxFrame{ 1 };
	if (image)
	{
		maxFrame = image->GetMaxFrameX() * image->GetMaxFrameY();
	}
	CurFrameIndex = IsAnimReverse ? maxFrame - 1 : 0;
	FrameSpeed = AnimData[CurState].second;
	FrameTime = 0.f;
	IsAnimEnd = false;
}

float Tornado::GetWidth()
{
	if (image)
	{
		return (float)image->GetFrameWidth();
	}
	return 0.0f;
}

float Tornado::GetHeight()
{
	if (image)
	{
		return (float)image->GetFrameHeight();
	}
	return 0.0f;
}

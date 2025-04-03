#include "BlimpEnemy.h"
#include "Image.h"
#include "Bullet.h"
#include "BrokenPiece.h"

#include "CommonFunction.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EffectManager.h"

namespace BlimpEnemyInfo
{
	string states[EState::STATE_END] = {"BlimpEnemyIdle", "BlimpEnemyAttack", "BlimpEnemyTurn"};
	string colors[EColor::COLOR_END] = { "PURPLE", "GREEN" };
}

BlimpEnemy::BlimpEnemy()
	: Dx{}, Dy{}, Color{ "GREEN" }, BulletNum{ 1 }, IsFired{},
	CurState{ BlimpEnemyInfo::EState::IDLE }, AnimData{}, IsAnimEnd{}, IsAnimReverse{}
{
}

BlimpEnemy::~BlimpEnemy()
{
}

void BlimpEnemy::Init(BlimpEnemyInfo::EColor _Color, int _BulletNum, FPOINT _Pos)
{
#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
	// GreenEnemy
	string stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::IDLE];
	string colorStr = BlimpEnemyInfo::colors[BlimpEnemyInfo::EColor::GREEN];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\a_blimp_enemy_idle.bmp"),
		2172, 95,
		12, 1,
		true, RGB(255, 0, 255));

	stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::ATTACK];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\a_blimp_enemy_attack.bmp"),
		1352, 95,
		8, 1,
		true, RGB(255, 0, 255));

	stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::TURN];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\a_blimp_enemy_turn.bmp"),
		1267, 106,
		7, 1,
		true, RGB(255, 0, 255));

	////////////////////////////////////////////////////
	// PurpleEnemy
	stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::IDLE];
	colorStr = BlimpEnemyInfo::colors[BlimpEnemyInfo::EColor::PURPLE];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\b_blimp_enemy_idle.bmp"),
		2160, 97,
		12, 1,
		true, RGB(255, 0, 255));

	stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::ATTACK];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\b_blimp_enemy_attack.bmp"),
		1344, 97,
		8, 1,
		true, RGB(255, 0, 255));

	stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::TURN];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\b_blimp_enemy_turn.bmp"),
		1267, 106,
		7, 1,
		true, RGB(255, 0, 255));
#pragma endregion

#pragma region Effect Image Load
	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyExplode",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Explode\\blimp_enemy_explode.bmp"),
		4172, 217,
		14, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"BlimpEnemySpark",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\Explode\\blimp_enemy_spark.bmp"),
		2232, 260,
		9, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	Dx = -1.f;
	Dy = 0.f;

	Color = BlimpEnemyInfo::colors[_Color];
	BulletNum = _BulletNum;
	IsFired = false;

	CurState = BlimpEnemyInfo::EState::STATE_END;
	
	// 일단 애니메이션 속도 전부 10.f
	for (int state = 0; state < BlimpEnemyInfo::EState::STATE_END; ++state)
	{
		AnimData.push_back({ BlimpEnemyInfo::states[state], 10.f });
	}

	SetState(BlimpEnemyInfo::EState::IDLE, false);

	Speed = 400.f;
	IsFlip = false;
	pos = _Pos;
	size = { 1.f,1.f };
	bDead = false;

	Hp = 4;

	float sizeX = GetWidth();
	float sizeY = GetHeight();
	MaxAlphaTime = 0.1f;

	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { sizeX * 0.5f, sizeY * 0.5f }, true, MaxAlphaTime);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_MONSTER);
}

void BlimpEnemy::Release()
{
}

void BlimpEnemy::Update()
{
	UpdateAlphaTime();

	UpdateFrame();

	UpdateState();

	Move();
}

void BlimpEnemy::Render(HDC hdc)
{
	//1. 배경
	//2. 배경오브젝트 back
	//3. Boss
	//4. BlimpEnemy			<--- 
	//5. Player
	//6. 이펙트
	//7. 배경오브젝트 front

	//if (image) image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, IsFlip);

	if (image)
	{
		if (0.f < AlphaTime)
		{
			image->FrameRenderAlpha(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, true, 30, RGB(255, 255, 255), IsFlip);
		}

		else
		{
			image->FrameRender(hdc, (int)pos.x, (int)pos.y, CurFrameIndex, 0, IsFlip);
			AlphaTime = 0.f;
		}
	}
}

void BlimpEnemy::UpdateFrame()
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

void BlimpEnemy::Move()
{
	pos.x += Dx * Speed * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += Dy * Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void BlimpEnemy::TakeDamage(int damage)
{
	Hp -= damage;

	AlphaTime = MaxAlphaTime * 0.5f;

	if (Hp <= 0)
	{
		bDead = true;
		EffectManager::GetInstance()->AddEffect("BlimpEnemySpark", pos, 1.f);
		EffectManager::GetInstance()->AddEffect("BlimpEnemyExplode", pos, 1.f);

		for (char pieceName = 'A'; pieceName <= 'F'; ++pieceName)
		{
			BrokenPiece* piece = new BrokenPiece((float)(uid(dre) % 2), (float)(uid(dre) % 4));
			piece->Init(pos, ("BlimpEnemyPiece" + string{pieceName} + Color));
			ObjectManager::GetInstance()->AddObject(piece, OBJ_MONSTER);
		}
	}
}

void BlimpEnemy::UpdateState()
{
	switch (CurState)
	{
	case BlimpEnemyInfo::EState::IDLE:
	{
		IDLE();
		break;
	}
	case BlimpEnemyInfo::EState::ATTACK:
	{
		ATTACK();
		break;
	}
	case BlimpEnemyInfo::EState::TURN:
	{
		TURN();
		break;
	}
	}
}

void BlimpEnemy::IDLE()
{
	if (!IsFired)
	{
		if (pos.x <= WINSIZE_X / 2)
		{
			Dx = 0.f;
			SetState(BlimpEnemyInfo::EState::ATTACK, false);
		}
	}
	else
	{
		if (OutOfScreen(pos, GetWidth(), GetHeight()))
		{
			bDead = true;
		}
	}if (!IsFired)
	{
		if (pos.x <= WINSIZE_X / 2)
		{
			Dx = 0.f;
			SetState(BlimpEnemyInfo::EState::ATTACK, false);
		}
	}
	else
	{
		if (OutOfScreen(pos, GetWidth(), GetHeight()))
		{
			bDead = true;
		}
	}
}

void BlimpEnemy::ATTACK()
{
	if (!IsAnimEnd) return;
	if (!IsAnimReverse)
	{
		FireBullet();
		SetState(BlimpEnemyInfo::EState::ATTACK, true);
	}
	else
	{
		SetState(BlimpEnemyInfo::EState::TURN, false);
	}
}

void BlimpEnemy::TURN()
{
	if (!IsAnimEnd) return;
	IsFlip = true;
	Dx = 1.f;
	SetState(BlimpEnemyInfo::EState::IDLE, false);
}

void BlimpEnemy::FireBullet()
{
	float defaultAngle{ 180.f };

	GameObject* target{};
	list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJTYPE::OBJ_PLAYER);
	if (!playerList.empty())
	{
		target = playerList.front();
	}

	if (target)
	{
		defaultAngle = (float)RAD_TO_DEG(GetAngle(pos, target->GetPos()));
	}

	// [-180, 180] -> [0, 360]
	defaultAngle = fmod((defaultAngle + 360.f), 360.f);
	defaultAngle = ClampValue(defaultAngle, 90.f, 270.f);

	for (int i = 0; i < BulletNum; ++i)
	{
		float bulletAngle = defaultAngle;
		if (BulletNum > 1)
		{
			bulletAngle = defaultAngle + 45.f - 90.f / (float)(BulletNum - 1) * i;
		}

		Bullet* bullet = new Bullet;
		FPOINT bulletPos = { pos.x - GetWidth() / 2, pos.y };
		bullet->Init(bulletPos, bulletAngle);

		ObjectManager::GetInstance()->AddObject(bullet, OBJTYPE::OBJ_MONSTER_WEAPON);
	}

	IsFired = true;
}

void BlimpEnemy::SetState(BlimpEnemyInfo::EState NewState, bool AnimReverse)
{
	if ((CurState == NewState) and (IsAnimReverse == AnimReverse)) return;

	CurState = NewState;
	IsAnimReverse = AnimReverse;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first + Color);
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

float BlimpEnemy::GetWidth()
{
	if (image)
	{
		return (float)image->GetFrameWidth();
	}
	return 0.0f;
}

float BlimpEnemy::GetHeight()
{
	if (image)
	{
		return (float)image->GetFrameHeight();
	}
	return 0.0f;
}

#include "BlimpEnemy.h"
#include "Image.h"

namespace BlimpEnemyInfo
{
	string states[EState::STATE_END] = {"BlimpEnemyIdle", "BlimpEnemyAttack", "BlimpEnemyTurn"};
	string colors[EColor::COLOR_END] = { "PURPLE", "GREEN" };
}

BlimpEnemy::BlimpEnemy()
{
}

BlimpEnemy::~BlimpEnemy()
{
}

void BlimpEnemy::Init()
{
#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
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

	Dx = -1.f;
	Dy = 0.f;

	Color = BlimpEnemyInfo::colors[BlimpEnemyInfo::EColor::PURPLE];
	BulletNum = 1;
	IsFired = false;
	CurState = BlimpEnemyInfo::EState::STATE_END;
	
	// 일단 애니메이션 속도 전부 10.f
	for (int state = BlimpEnemyInfo::EState::IDLE; state < BlimpEnemyInfo::EState::STATE_END; ++state)
	{
		AnimData.push_back({ BlimpEnemyInfo::states[state], 10.f });
	}

	SetState(BlimpEnemyInfo::EState::IDLE, false);

	Speed = 200.f;
	IsFlip = false;
	pos = { WINSIZE_X, WINSIZE_Y / 2 };
	size = { 1.f,1.f };
	bDead = false;
}

void BlimpEnemy::Release()
{
}

void BlimpEnemy::Update()
{
	UpdateState();

	Move();

	UpdateFrame();
}

void BlimpEnemy::Render(HDC hdc)
{
	//1. 배경
	//2. 배경오브젝트 back
	//3. BlimpEnemy			<--- 
	//4. Boss
	//5. Player
	//6. 이펙트
	//7. 배경오브젝트 front

	if (image) image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, IsFlip);
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

void BlimpEnemy::UpdateState()
{
	if (!IsAnimEnd) return;

	switch (CurState)
	{
	case BlimpEnemyInfo::EState::IDLE:
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
			float imgSize{};
			if (image)
			{
				imgSize = image->GetFrameWidth();
			}

			if (pos.x > WINSIZE_X + imgSize / 2)
			{
				bDead = true;
			}
		}
		break;
	}
	case BlimpEnemyInfo::EState::ATTACK:
	{
		if (!IsAnimReverse)
		{
			// FireBullet use BulletNum
			IsFired = true;

			SetState(BlimpEnemyInfo::EState::ATTACK, true);
		}
		else
		{
			SetState(BlimpEnemyInfo::EState::TURN, false);
		}
		break;
	}
	case BlimpEnemyInfo::EState::TURN:
	{
		IsFlip = true;
		Dx = 1.f;
		SetState(BlimpEnemyInfo::EState::IDLE, false);
		break;
	}
	}
}

void BlimpEnemy::SetColor(string _Color)
{
	Color = _Color;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first + Color);
}

void BlimpEnemy::SetState(BlimpEnemyInfo::EState NewState, bool AnimReverse)
{
	if ((CurState == NewState) and (IsAnimReverse == AnimReverse)) return;

	CurState = NewState;
	IsAnimReverse = AnimReverse;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first + Color);
	int maxFrame{};
	if (image)
	{
		maxFrame = image->GetMaxFrameX() * image->GetMaxFrameY();
	}
	CurFrameIndex = IsAnimReverse ? maxFrame - 1 : 0;
	FrameSpeed = AnimData[CurState].second;
	FrameTime = 0.f;
	IsAnimEnd = false;
}

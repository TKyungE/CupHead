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
		1690, 90,
		10, 1,
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
		1680, 97,
		10, 1,
		true, RGB(255, 0, 255));

	stateStr = BlimpEnemyInfo::states[BlimpEnemyInfo::EState::TURN];
	ImageManager::GetInstance()->AddImage(
		stateStr + colorStr,
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\b_blimp_enemy_turn.bmp"),
		1267, 106,
		7, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	Color = BlimpEnemyInfo::colors[BlimpEnemyInfo::EColor::PURPLE];
	BulletNum = 1;
	CurState = BlimpEnemyInfo::EState::STATE_END;
	
	// 일단 애니메이션 속도 전부 0.5f
	for (int state = BlimpEnemyInfo::EState::IDLE; state < BlimpEnemyInfo::EState::STATE_END; ++state) {
		AnimData.push_back({ BlimpEnemyInfo::states[state], 10.f });
	}

	SetState(BlimpEnemyInfo::EState::IDLE);

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
	// 화면 중앙 쯤까지 Idle 이미지로 이동 dx < 0
	// 잠시 멈췄다가
	// Attack 재생
	// 재생 끝나면 총알 발사
	// Attack 역재생
	// Turn
	// Idle 화면 밖으로 이동 flip = true, dx > 0
	switch (CurState)
	{
	case BlimpEnemyInfo::EState::IDLE:
	{
		if (pos.x > WINSIZE_X / 2) {
			pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();
		}
		break;
	}
	case BlimpEnemyInfo::EState::ATTACK:
	{
		break;
	}
	case BlimpEnemyInfo::EState::TURN:
	{
		break;
	}
	}

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

void BlimpEnemy::SetState(BlimpEnemyInfo::EState NewState)
{
	if (CurState == NewState) return;

	CurState = NewState;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first + Color);
	CurFrameIndex = 0;
	FrameSpeed = AnimData[CurState].second;
	FrameTime = 0.f;
}

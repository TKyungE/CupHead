#include "BlimpEnemy.h"
#include "Image.h"

BlimpEnemy::BlimpEnemy()
{
}

BlimpEnemy::~BlimpEnemy()
{
}

void BlimpEnemy::Init()
{
	AnimData[BlimpEnemyState::Idle] = { "BlimpEnemyIdle", 1.0f };
	AnimData[BlimpEnemyState::Attack] = { "BlimpEnemyAttack", 1.0f };
	AnimData[BlimpEnemyState::Turn] = { "BlimpEnemyTurn", 1.0f };

	// Image 나중에 다른데서 한꺼번에 Loading 
	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyIdle",
		L"Image\CupHead\Hilda Berg\Enemy\EnemyGreen\a_blimp_enemy_idle.bmp",
		2172, 95,
		12, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyAttack",
		L"Image\CupHead\Hilda Berg\Enemy\EnemyGreen\a_blimp_enemy_attack.bmp",
		1690, 90,
		10, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		"BlimpEnemyTurn",
		L"Image\CupHead\Hilda Berg\Enemy\EnemyGreen\a_blimp_enemy_turn.bmp",
		1267, 106,
		7, 1,
		true, RGB(255, 0, 255));

	CurState = BlimpEnemyState::Idle;
	image = ImageManager::GetInstance()->FindImage(AnimData[CurState].first);
	FrameSpeed = AnimData[CurState].second;
	
	// y 값 위아래 랜덤으로 변경해야 함
	pos = { WINSIZE_X + (float)image->GetFrameWidth() / 2, WINSIZE_Y };
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
}

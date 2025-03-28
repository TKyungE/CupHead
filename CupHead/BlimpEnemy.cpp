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

	// Image ���߿� �ٸ����� �Ѳ����� Loading 
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
	
	// y �� ���Ʒ� �������� �����ؾ� ��
	pos = { WINSIZE_X + (float)image->GetFrameWidth() / 2, WINSIZE_Y };
}

void BlimpEnemy::Release()
{
}

void BlimpEnemy::Update()
{
	// ȭ�� �߾� ����� Idle �̹����� �̵� dx < 0
	// ��� ����ٰ�
	// Attack ���
	// ��� ������ �Ѿ� �߻�
	// Attack �����
	// Turn
	// Idle ȭ�� ������ �̵� flip = true, dx > 0
}

void BlimpEnemy::Render(HDC hdc)
{
	//1. ���
	//2. ��������Ʈ back
	//3. BlimpEnemy			<--- 
	//4. Boss
	//5. Player
	//6. ����Ʈ
	//7. ��������Ʈ front
}

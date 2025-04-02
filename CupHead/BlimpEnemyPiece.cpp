#include "BlimpEnemyPiece.h"
#include "Image.h"
#include "CommonFunction.h"

namespace BlimpEnemyPieceInfo
{
	string types[EType::TYPE_END] = {
		"BlimpEnemyPieceA",
		"BlimpEnemyPieceB",
		"BlimpEnemyPieceC",
		"BlimpEnemyPieceD",
		"BlimpEnemyPieceE",
		"BlimpEnemyPieceF",
	};
}

BlimpEnemyPiece::BlimpEnemyPiece(float _Dx, float _Dy)
	: Dx{ _Dx }, Dy{ _Dy }
{
}

BlimpEnemyPiece::~BlimpEnemyPiece()
{
}

void BlimpEnemyPiece::Init(FPOINT _pos, BlimpEnemyPieceInfo::EType Type, string Color)
{
	string typeStr{};
#pragma region Image Load
	typeStr = BlimpEnemyPieceInfo::types[BlimpEnemyPieceInfo::EType::A];
	ImageManager::GetInstance()->AddImage(
		typeStr + "GREEN",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\Piece\\a_blimp_enemy_piece_A.bmp"),
		544, 65,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		typeStr + "PURPLE",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\Piece\\b_blimp_enemy_piece_A.bmp"),
		536, 66,
		8, 1,
		true, RGB(255, 0, 255));

	typeStr = BlimpEnemyPieceInfo::types[BlimpEnemyPieceInfo::EType::B];
	ImageManager::GetInstance()->AddImage(
		typeStr + "GREEN",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\Piece\\a_blimp_enemy_piece_B.bmp"),
		528, 61,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		typeStr + "PURPLE",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\Piece\\b_blimp_enemy_piece_B.bmp"),
		520, 62,
		8, 1,
		true, RGB(255, 0, 255));

	typeStr = BlimpEnemyPieceInfo::types[BlimpEnemyPieceInfo::EType::C];
	ImageManager::GetInstance()->AddImage(
		typeStr + "GREEN",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\Piece\\a_blimp_enemy_piece_C.bmp"),
		424, 53,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		typeStr + "PURPLE",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\Piece\\b_blimp_enemy_piece_C.bmp"),
		416, 54,
		8, 1,
		true, RGB(255, 0, 255));

	typeStr = BlimpEnemyPieceInfo::types[BlimpEnemyPieceInfo::EType::D];
	ImageManager::GetInstance()->AddImage(
		typeStr + "GREEN",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\Piece\\a_blimp_enemy_piece_D.bmp"),
		464, 58,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		typeStr + "PURPLE",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\Piece\\b_blimp_enemy_piece_D.bmp"),
		448, 58,
		8, 1,
		true, RGB(255, 0, 255));

	typeStr = BlimpEnemyPieceInfo::types[BlimpEnemyPieceInfo::EType::E];
	ImageManager::GetInstance()->AddImage(
		typeStr + "GREEN",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\Piece\\a_blimp_enemy_piece_E.bmp"),
		456, 56,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		typeStr + "PURPLE",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\Piece\\b_blimp_enemy_piece_E.bmp"),
		440, 56,
		8, 1,
		true, RGB(255, 0, 255));

	typeStr = BlimpEnemyPieceInfo::types[BlimpEnemyPieceInfo::EType::F];
	ImageManager::GetInstance()->AddImage(
		typeStr + "GREEN",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyGreen\\Piece\\a_blimp_enemy_piece_F.bmp"),
		496, 62,
		8, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(
		typeStr + "PURPLE",
		TEXT("Image\\CupHead\\Hilda Berg\\Enemy\\EnemyPurple\\Piece\\b_blimp_enemy_piece_F.bmp"),
		480, 62,
		8, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	typeStr = BlimpEnemyPieceInfo::types[Type];
	image = ImageManager::GetInstance()->FindImage(typeStr + Color);

	CurFrameIndex = 0;
	FrameSpeed = 10.f;
	FrameTime = 0.f;

	Speed = 450.f;
	IsFlip = false;
	pos = _pos;
	size = { 1.f,1.f };
	bDead = false;
}

void BlimpEnemyPiece::Release()
{
}

void BlimpEnemyPiece::Update()
{
	UpdateFrame();
	UpdateDy();
	Move();

	if (OutOfScreen(pos, 10, 10))
	{
		bDead = true;
	}
}

void BlimpEnemyPiece::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, 0);
}

void BlimpEnemyPiece::Move()
{
	pos.x += Dx * Speed * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += Dy * Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void BlimpEnemyPiece::UpdateDy()
{
	Dy += 4.f * TimerManager::GetInstance()->GetDeltaTime();
	Dy = ClampValue(Dy, -10.f, 10.f);
}

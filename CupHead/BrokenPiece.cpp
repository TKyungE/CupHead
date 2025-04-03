#include "BrokenPiece.h"
#include "Image.h"
#include "CommonFunction.h"

BrokenPiece::BrokenPiece(float _Dx, float _Dy)
	: Dx{ _Dx }, Dy{ _Dy }
{
}

BrokenPiece::~BrokenPiece()
{
}

void BrokenPiece::Init(FPOINT _pos, string ImageName)
{
	InitImage();
	image = ImageManager::GetInstance()->FindImage(ImageName);

	CurFrameIndex = 0;
	FrameSpeed = 10.f;
	FrameTime = 0.f;

	Speed = 450.f;
	IsFlip = false;
	pos = _pos;
	size = { 1.f,1.f };
	bDead = false;
}

void BrokenPiece::Release()
{
}

void BrokenPiece::Update()
{
	UpdateFrame();
	UpdateDy();
	Move();

	if (OutOfScreen(pos, 10, 10))
	{
		bDead = true;
	}
}

void BrokenPiece::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, 0);
}

void BrokenPiece::Move()
{
	pos.x += Dx * Speed * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += Dy * Speed * TimerManager::GetInstance()->GetDeltaTime();
}

void BrokenPiece::InitImage()
{
	string typeStr{};
#pragma region blimp enemy piece Image Load
	typeStr = "BlimpEnemyPieceA";
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

	typeStr = "BlimpEnemyPieceB";
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

	typeStr = "BlimpEnemyPieceC";
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

	typeStr = "BlimpEnemyPieceD";
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

	typeStr = "BlimpEnemyPieceE";
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

	typeStr = "BlimpEnemyPieceF";
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

#pragma region player plane piece Image Load

#pragma endregion
	// add this code when player turn into death state
	//for (char pieceName = 'a'; pieceName <= 'e'; ++pieceName)
	//{
	//	BrokenPiece* piece = new BrokenPiece((float)(uid(dre) % 2), (float)(uid(dre) % 4));
	//	piece->Init(pos, ("schmup_ch_piece_" + string{ pieceName }));
	//	ObjectManager::GetInstance()->AddObject(piece, OBJ_MONSTER);
	//}
	//for (char pieceName = 'a'; pieceName <= 'd'; ++pieceName)
	//{
	//	BrokenPiece* piece = new BrokenPiece((float)(uid(dre) % 2), (float)(uid(dre) % 4));
	//	piece->Init(pos, ("schmup_gear_" + string{ pieceName }));
	//	ObjectManager::GetInstance()->AddObject(piece, OBJ_MONSTER);
	//}
}

void BrokenPiece::UpdateDy()
{
	Dy += 4.f * TimerManager::GetInstance()->GetDeltaTime();
	Dy = ClampValue(Dy, -10.f, 10.f);
}

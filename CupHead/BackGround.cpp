#include "BackGround.h"
#include "Image.h"
#include "ImageManager.h"

namespace BackGroundInfo
{
	string BackGroundTypes[EBackGroundType::BACKTYPE_END] = {
		"SKY",
		"CLOUD",
		"DARK_HILL",
		"MAIN_GROUND"
	};
	int BackGroundNum[EBackGroundType::BACKTYPE_END] = { 1, 5, 1, 2 };

	string ForeGroundTypes[EForeGroundType::FORETYPE_END] = {
		"LARGE_FOREST",
		"MEDIUM_FOREST",
		"SMALL_FOREST_A",
		"SMALL_FOREST_B",
	};
	int ForeGroundNum[EForeGroundType::FORETYPE_END] = { 7, 4, 6, 4 };

	string ForeObject = { "FOREOBJECT" };
	int ForeObjectNum = 6;
}

BackGround::BackGround(FPOINT InPos, Image* _image, int _Speed, bool _Loop)
	: StartPos(InPos), image(_image), Speed(_Speed), IsOut{ true }, Loop(_Loop)
{
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	pos = StartPos;
	IsOut = false;
}

void BackGround::Update()
{
	if (Speed)
		pos.x -= Speed * TimerManager::GetInstance()->GetDeltaTime();

	int width{};
	if (image) width = image->GetFrameWidth();

	if (Loop)
	{
		if (pos.x <= 0)
		{
			pos.x = WINSIZE_X;
		}
	}
	else
	{
		if (pos.x + width <= 0)
		{
			IsOut = true;
		}
	}
}

void BackGround::Render(HDC hdc)
{
	if (IsOut) return;
	if (image != nullptr)
	{
		if (!Loop)
		{
			image->FrameRender(hdc, pos.x, pos.y, 0, 0);
		}
		else
		{
			image->FrameRender(hdc, pos.x, pos.y, 0, 0);
		}
	}
}

float BackGround::GetRightPos() const
{
	int width{};
	if (image) width = image->GetFrameWidth();
	return pos.x + width / 2.f;
}

void BackGround::Release()
{
}

BackGroundManager::BackGroundManager()
	: MainGroundIndex{},
	BackGroundList{}, ForeGroundList{}, ForeObjectList{},
	SelectedForeGround{}, ForeGroundElapsedTime{}, ForeGroundCoolTime{}
{
}

BackGroundManager::~BackGroundManager()
{
}

void BackGroundManager::Init()
{
	BackGroundInfo::EBackGroundType imageBackType{};
	BackGroundInfo::EForeGroundType imageForeType{};
	int imageNum{};
#pragma region Image Load
	// Image 나중에 다른데서 한꺼번에 Load
	// background
#pragma region sky
	imageBackType = BackGroundInfo::EBackGroundType::SKY;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_sky.bmp"),
		1540, 900,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region cloud
	// cloud
	imageBackType = BackGroundInfo::EBackGroundType::CLOUD;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_clouds_0001.bmp"),
		1596, 378,
		1, 1,
		true, RGB(255, 0, 255));

	++imageNum;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_clouds_0002.bmp"),
		1047, 244,
		1, 1,
		true, RGB(255, 0, 255));

	++imageNum;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_clouds_0003.bmp"),
		1851, 301,
		1, 1,
		true, RGB(255, 0, 255));

	++imageNum;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_clouds_0004.bmp"),
		1836, 376,
		1, 1,
		true, RGB(255, 0, 255));

	++imageNum;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_clouds_0005.bmp"),
		2048, 322,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region dark hill
	// dark hill
	imageBackType = BackGroundInfo::EBackGroundType::DARK_HILL;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_dark_hills.bmp"),
		2048, 268,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region main ground
	// main ground
	imageBackType = BackGroundInfo::EBackGroundType::MAIN_GROUND;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_main_ground_0001.bmp"),
		2048, 227,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::BackGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_main_ground_0002.bmp"),
		2048, 207,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	// foreground
#pragma region large forest
	// large forest
	imageForeType = BackGroundInfo::EForeGroundType::LARGE_FOREST;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0000.bmp"),
		146, 358,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0001.bmp"),
		146, 358,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0002.bmp"),
		1099, 233,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0002b.bmp"),
		122, 266,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0003.bmp"),
		1421, 283,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0003b.bmp"),
		82, 166,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_large_forest_0004.bmp"),
		1382, 257,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region medium forest
	// medium forest
	imageForeType = BackGroundInfo::EForeGroundType::MEDIUM_FOREST;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_medium_forest_0001.bmp"),
		1205, 285,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_medium_forest_0002.bmp"),
		1265, 273,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_medium_forest_0003.bmp"),
		752, 227,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_medium_forest_0004.bmp"),
		1155, 242,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region small_forest_A
	// small forest A
	imageForeType = BackGroundInfo::EForeGroundType::SMALL_FOREST_A;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_A_0000.bmp"),
		296, 298,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_A_0001.bmp"),
		1148, 236,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_A_0002.bmp"),
		640, 209,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_A_0002b.bmp"),
		93, 219,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_A_0003.bmp"),
		746, 245,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_A_0004.bmp"),
		1185, 164,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma region small_forest_B
	// small forest B
	imageForeType = BackGroundInfo::EForeGroundType::SMALL_FOREST_B;
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_B_0001.bmp"),
		835, 247,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_B_0002.bmp"),
		645, 196,
		1, 1,
		true, RGB(255, 0, 255));
	
	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_B_0003.bmp"),
		933, 199,
		1, 1,
		true, RGB(255, 0, 255));
	
	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeGroundTypes[imageBackType] + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\blimp_small_forest_B_0004.bmp"),
		1239, 246,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion

	// foreObject
#pragma region foreObject
	imageNum = 0;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeObject + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\DayForeground\\blimp_foreground_bunny.bmp"),
		115, 406,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeObject + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\DayForeground\\blimp_foreground_instrument.bmp"),
		201, 251,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeObject + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\DayForeground\\blimp_foreground_mirror.bmp"),
		123, 485,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeObject + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\DayForeground\\blimp_foreground_reciever.bmp"),
		106, 249,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeObject + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\DayForeground\\blimp_foreground_sock.bmp"),
		178, 365,
		1, 1,
		true, RGB(255, 0, 255));

	imageNum++;
	ImageManager::GetInstance()->AddImage(
		BackGroundInfo::ForeObject + to_string(imageNum),
		TEXT("Image\\CupHead\\BackGround\\Day\\DayForeground\\blimp_foreground_tower.bmp"),
		134, 283,
		1, 1,
		true, RGB(255, 0, 255));
#pragma endregion
#pragma endregion

	// back
	// sky 1
	imageBackType = BackGroundInfo::EBackGroundType::SKY;
	imageNum = 0;
	string imageName = BackGroundInfo::BackGroundTypes[BackGroundInfo::EBackGroundType::SKY] + to_string(imageNum);
	Image* image = ImageManager::GetInstance()->FindImage(imageName);
	int fw = 0;
	int fh = 0;
	if (image)
	{
		fw = image->GetFrameWidth();
		fh = image->GetFrameHeight();
	}
	BackGround* background = new BackGround({ WINSIZE_X / 2.f, WINSIZE_Y / 2.f }, image, 1, true);
	background->Init();
	BackGroundList[imageBackType].emplace_back(background);

	// cloud
	imageBackType = BackGroundInfo::EBackGroundType::CLOUD;
	imageNum = 0;
	imageName = BackGroundInfo::BackGroundTypes[BackGroundInfo::EBackGroundType::CLOUD] + to_string(imageNum);
	image = ImageManager::GetInstance()->FindImage(imageName);
	fw = 0;
	fh = 0;
	if (image)
	{
		fw = image->GetFrameWidth();
		fh = image->GetFrameHeight();
	}
	background = new BackGround({ WINSIZE_X / 2.f, WINSIZE_Y / 4.f }, image, 10, false);
	background->Init();
	BackGroundList[imageBackType].emplace_back(background);

	// dark hill
	imageBackType = BackGroundInfo::EBackGroundType::DARK_HILL;
	imageNum = 0;
	imageName = BackGroundInfo::BackGroundTypes[BackGroundInfo::EBackGroundType::DARK_HILL] + to_string(imageNum);
	image = ImageManager::GetInstance()->FindImage(imageName);
	fw = 0;
	fh = 0;
	if (image)
	{
		fw = image->GetFrameWidth();
		fh = image->GetFrameHeight();
	}
	background = new BackGround({ WINSIZE_X / 2.f, WINSIZE_Y - fh/2.f }, image, 100, false);
	background->Init();
	BackGroundList[imageBackType].emplace_back(background);

	
	// main ground
	imageBackType = BackGroundInfo::EBackGroundType::MAIN_GROUND;
	imageNum = 0;
	imageName = BackGroundInfo::BackGroundTypes[BackGroundInfo::EBackGroundType::MAIN_GROUND] + to_string(imageNum);
	image = ImageManager::GetInstance()->FindImage(imageName);
	fw = 0;
	fh = 0;
	if (image)
	{
		fw = image->GetFrameWidth();
		fh = image->GetFrameHeight();
	}
	background = new BackGround({ WINSIZE_X + fw/2.f, WINSIZE_Y - fh/2.f }, image, 500, false);
	background->Init();
	BackGroundList[imageBackType].emplace_back(background);

	imageBackType = BackGroundInfo::EBackGroundType::MAIN_GROUND;
	imageNum++;
	imageName = BackGroundInfo::BackGroundTypes[BackGroundInfo::EBackGroundType::MAIN_GROUND] + to_string(imageNum);
	image = ImageManager::GetInstance()->FindImage(imageName);
	fw = 0;
	fh = 0;
	if (image)
	{
		fw = image->GetFrameWidth();
		fh = image->GetFrameHeight();
	}
	background = new BackGround({ WINSIZE_X + fw/2.f, WINSIZE_Y - fh/2.f }, image, 500, false);
	//background->Init();
	BackGroundList[imageBackType].emplace_back(background);




}

void BackGroundManager::Release()
{
	for (int i = 0; i < BackGroundInfo::EBackGroundType::BACKTYPE_END; ++i)
	{
		for (BackGround* bg : BackGroundList[i])
		{
			bg->Release();
			delete bg;
			bg = NULL;
		}
	}
	
	for (int i = 0; i < BackGroundInfo::EForeGroundType::FORETYPE_END; ++i)
	{
		for (BackGround* bg : ForeGroundList[i])
		{
			bg->Release();
			delete bg;
			bg = NULL;
		}
	}

	for (BackGround* bg : ForeObjectList)
	{
		bg->Release();
		delete bg;
		bg = NULL;
	}
}

void BackGroundManager::Update()
{
	PrepareNextBackGround();
	PrepareNextForeGround();

	for (int i = 0; i < BackGroundInfo::EBackGroundType::BACKTYPE_END; ++i)
	{
		for (BackGround* bg : BackGroundList[i])
		{
			bg->Update();
		}
	}

	for (BackGround* bg : ForeGroundList[SelectedForeGround])
	{
		bg->Update();
	}

	for (BackGround* bg : ForeObjectList)
	{
		bg->Update();
	}
}

void BackGroundManager::RenderBackGround(HDC hdc)
{
	for (int i = 0; i < BackGroundInfo::EBackGroundType::BACKTYPE_END; ++i)
	{
		for (BackGround* bg : BackGroundList[i])
		{
			bg->Render(hdc);
		}
	}
}

void BackGroundManager::RenderForeGround(HDC hdc)
{
	for (BackGround* bg : ForeGroundList[SelectedForeGround])
	{
		bg->Render(hdc);
	}

	for (BackGround* bg : ForeObjectList)
	{
		bg->Render(hdc);
	}
}

void BackGroundManager::PrepareNextBackGround()
{
	BackGround* mainGround = BackGroundList[BackGroundInfo::EBackGroundType::MAIN_GROUND][MainGroundIndex];
	if (mainGround->GetRightPos() <= WINSIZE_X / 2.f)
	{
		MainGroundIndex++;
		MainGroundIndex %= BackGroundList[BackGroundInfo::EBackGroundType::MAIN_GROUND].size();
		if (BackGroundList[BackGroundInfo::EBackGroundType::MAIN_GROUND][MainGroundIndex])
		{
			BackGroundList[BackGroundInfo::EBackGroundType::MAIN_GROUND][MainGroundIndex]->Init();
		}
	}
}

void BackGroundManager::PrepareNextForeGround()
{
	bool foreEnd{ true };
	for (BackGround* bg : ForeGroundList[SelectedForeGround])
	{
		if (!bg->IsOutOfScreen())
		{
			foreEnd = false;
			break;
		}
	}

	if (!foreEnd) return;

	ForeGroundElapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (ForeGroundElapsedTime < ForeGroundCoolTime) return;

	SelectedForeGround++;
	SelectedForeGround %= BackGroundInfo::EForeGroundType::FORETYPE_END;

	for (BackGround* bg : ForeGroundList[SelectedForeGround])
	{
		bg->Init();
	}

	ForeGroundElapsedTime = 0.f;
	ForeGroundCoolTime = uid(dre) % 6 + 2.f;
}

void BackGroundManager::PrepareNextForeObject()
{
}

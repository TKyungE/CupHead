#include "PlayerHP.h"
#include "Image.h"
#include "ImageManager.h"
#include "ObjectManager.h"
#include "Character.h"
#include "CommonFunction.h"

PlayerHP::PlayerHP()
	:Player(nullptr), bHP1SettingReset(false)
{
}

void PlayerHP::Init()
{
	image = ImageManager::GetInstance()->AddImage("PlayerHP", L"Image/CupHead/UI/Player/HP/PlayerHP.bmp", 481, 69, 6, 2, true, RGB(255, 0, 255));

	pos = { (float)image->GetFrameWidth() * 0.5f,WINSIZE_Y - (float)image->GetFrameHeight() * 0.5f };
}

void PlayerHP::Update()
{
	if (Player == nullptr)
	{
		list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJ_PLAYER);
		if (!playerList.empty())
			Player = dynamic_cast<Character*>(playerList.front());
	}

	HPUpdate();
}

void PlayerHP::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, CurFrameYIndex);
}

void PlayerHP::HPUpdate()
{
	if (Player == nullptr)
		return;

	if (Player->GetHp() != 1)
		bHP1SettingReset = false;

	CurFrameYIndex = ClampValue<int>(Player->GetHp() / 4, 0, 1);

	if (Player->GetHp() == 1)
	{
		if (!bHP1SettingReset)
			HP1SettingReset();

		FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
		CurFrameIndex = (int)FrameTime;

		if (CurFrameIndex > 3)
			CurFrameIndex = FrameTime = 2;
	}
	else if (Player->GetHp() == 2 || Player->GetHp() == 3)
		CurFrameIndex = Player->GetHp() + 2;
	else if (Player->GetHp() >= 4)
		CurFrameIndex = ClampValue(Player->GetHp() - 4, 0, 4);
	else
		CurFrameIndex = Player->GetHp();
}

void PlayerHP::HP1SettingReset()
{
	bHP1SettingReset = true;

	FrameSpeed = 10.f;
	FrameTime = 2.f;
}

void PlayerHP::Release()
{
	Player = nullptr;
}

PlayerHP::~PlayerHP()
{
}

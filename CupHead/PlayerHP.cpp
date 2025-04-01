#include "PlayerHP.h"
#include "Image.h"
#include "ImageManager.h"
#include "ObjectManager.h"
#include "Character.h"
#include "CommonFunction.h"

PlayerHP::PlayerHP()
	:Owner(nullptr), bHP1SettingReset(false)
{
}

void PlayerHP::Init()
{
	FrameSpeed = 10.f;

	image = ImageManager::GetInstance()->AddImage("PlayerHP", L"Image/CupHead/UI/Player/HP/PlayerHP.bmp", 481, 69, 6, 2, true, RGB(255, 0, 255));

	pos = { (float)image->GetFrameWidth() * 0.5f,WINSIZE_Y - (float)image->GetFrameHeight() * 0.5f };
}

void PlayerHP::Update()
{
	if (Owner == nullptr)
	{
		list<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(OBJ_PLAYER);
		if (!playerList.empty())
			Owner = dynamic_cast<Character*>(playerList.front());
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
	if (Owner == nullptr)
		return;

	if (Owner->GetHp() != 1)
		bHP1SettingReset = false;

	CurFrameYIndex = ClampValue<int>(Owner->GetHp() / 4, 0, 1);

	if (Owner->GetHp() == 1)
	{
		if (!bHP1SettingReset)
			HP1SettingReset();

		FrameTime += FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
		CurFrameIndex = (int)FrameTime;

		if (CurFrameIndex > 3)
			CurFrameIndex = FrameTime = 2;
	}
	else if (Owner->GetHp() == 2 || Owner->GetHp() == 3)
		CurFrameIndex = Owner->GetHp() + 2;
	else if (Owner->GetHp() >= 4)
		CurFrameIndex = ClampValue(Owner->GetHp() - 4, 0, 4);
	else
		CurFrameIndex = Owner->GetHp();
}

void PlayerHP::HP1SettingReset()
{
	bHP1SettingReset = true;
	
	FrameTime = 2.f;
}

void PlayerHP::Release()
{
	Owner = nullptr;
}

PlayerHP::~PlayerHP()
{
}

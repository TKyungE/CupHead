#include "OrbBullet.h"
#include "Image.h"
#include "ImageManager.h"

OrbBullet::OrbBullet(FPOINT InPos)
{
	pos = InPos;
	FrameSpeed = 1.f;
	Speed = 7893.f / 43;
}

void OrbBullet::Init()
{
	image = ImageManager::GetInstance()->AddImage("orb_bullet_stream", L"Image/CupHead/Hilda Berg/Gemini/Attack/orb_bullet_stream.bmp", 7893, 43, 9, 1, true, RGB(255, 0, 255));
}

void OrbBullet::Release()
{
}

void OrbBullet::Update()
{
	UpdateFrame();

	Move();
}

void OrbBullet::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x - 7893 / 43 * 0.5f, pos.y - (image->GetHeight() * 0.5f), CurFrameIndex);
}

void OrbBullet::Move()
{
	/*pos.x += Speed * TimerManager::GetInstance()->GetDeltaTime();*/
}

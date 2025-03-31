#include "Player.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "ObjectManager.h"
#include "CommonFunction.h"
#include "PlayerMissile.h"

Player::Player() 
	: FrameDir(1), FireCnt(0), FireTime(0.f), FireCoolTime(0.07f), IsTranseEnd(false), PreUpDownState(UPDOWN_NONE), CurUpDownState(UPDOWN_NONE), PreState(PLAYER_IDLE), CurState(PLAYER_IDLE), NextImage(nullptr)
{

}				  

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Init(FPOINT pos, FPOINT size)
{
	this->pos = pos;
	this->size = size;

	Speed = 700.f;
	FrameSpeed = 30.f;
	//FrameSpeed = 25.f;

	ImageInit();
	Collider* collider = new Collider(this, COLLIDERTYPE::Rect, { 0.f,0.f }, { 105.f, 85.f }, true);
	collider->Init();
	CollisionManager::GetInstance()->AddCollider(collider, OBJTYPE::OBJ_PLAYER);

	EffectTestInit();										
	//EffectManager::GetInstance()->AddEffect("blimp_star_fx", pos, 30.f, { 100.f, 0.f }, 30, true, this);
	//image이름, 초기 위치, 몇 초 동안 보일건지, 초기 위치 기준 offset 위치, 몇 번 반복하고 싶은지, GameObj Trece 여부, Trace할거면 포인터 넣기
	// EffectManager::GetInstance()->AddEffectDefault("blimp_star_fx", pos, 30.f);
	// 그냥 그 위치에 한 번 터트리기만 할 거면 Default 쓰기
}

void Player::Release()
{

}

void Player::Update()
{
	Move();
	Action();
	UpdateState();
	UpdateFrame();
}

void Player::UpdateFrame()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	if (-1 == FrameDir)
	{
		FrameTime += FrameDir * 1.5f * FrameSpeed * DeltaTime; //Gara
	}

	else
	{
		FrameTime += FrameDir * FrameSpeed * DeltaTime;
	}
	
	CurFrameIndex = (int)FrameTime;

	if (-1 == FrameDir && UPDOWN_NONE != CurUpDownState)
	{
		if (0 > CurFrameIndex)
		{
			FrameDir = 1;
			if (nullptr != NextImage)
			{
				image = NextImage;
				NextImage = nullptr;
			}

			if (UPDOWN_UP == CurUpDownState)
			{
				NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_up");
			}

			else if (UPDOWN_DOWN == CurUpDownState)
			{
				NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_down");
			}

			CurFrameIndex = FrameTime = 0.f;
		}
	}

	else if (-1 == FrameDir && UPDOWN_NONE == CurUpDownState)
	{
		if (0 > CurFrameIndex)
		{
			FrameDir = 1;
			if (nullptr != NextImage)
			{
				image = NextImage;
				NextImage = nullptr;
			}

			CurFrameIndex = FrameTime = 0.f;
		}
	}

	else if (UPDOWN_NONE != CurUpDownState)
	{
		if (CurFrameIndex >= image->GetMaxFrameX())
		{
			//FrameDir = 1;
			if (nullptr != NextImage)
			{
				image = NextImage;
				NextImage = nullptr;
			}
			CurFrameIndex = FrameTime = 0.f;
		}
	}

	else if (CurFrameIndex >= image->GetMaxFrameX())
	{
		CurFrameIndex = FrameTime = 0.f;
	}
}

void Player::UpdateInput()
{

}

void Player::UpdateState()
{
	if (PreState != CurState)
	{
		switch (CurState)
		{
		case PLAYER_IDLE:
			break;
		case PLAYER_MOVE:
			break;
		case PLAYER_ATTACK:
			break;
		case PLAYER_END:
			break;
		default:
			break;
		}
	}

	PreState = CurState;

	if (PreUpDownState == CurUpDownState)
	{
		return;
	}

	switch(CurUpDownState)
	{
	case UPDOWN_UP:
		UpdateToUpState();
		break;
	case UPDOWN_DOWN:
		UpdateToDownState();
		break;
	case UPDOWN_NONE:
		UpdateToNoneState();
		break;
	default:
		break;
	}
	PreUpDownState = CurUpDownState;
}

void Player::UpdateToUpState()
{
	if (-1 == FrameDir)
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			break;
		case UPDOWN_UP:
			break;
		case UPDOWN_DOWN:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}

	else
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_up");
			FrameDir = 1;
			break;
		case UPDOWN_UP:
			break;
		case UPDOWN_DOWN:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			FrameDir = -1;
			CurFrameIndex = FrameTime = image->GetMaxFrameX();
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}
}

void Player::UpdateToDownState()
{
	if (-1 == FrameDir)
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			break;
		case UPDOWN_UP:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			break;
		case UPDOWN_DOWN:
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}

	else
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_down");
			FrameDir = 1;
			break;
		case UPDOWN_UP:
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			FrameDir = -1;
			CurFrameIndex = FrameTime = image->GetMaxFrameX();
			break;
		case UPDOWN_DOWN:
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}
}

void Player::UpdateToNoneState()
{
	//if (-1 == FrameDir)
	//{
	//	switch (PreUpDownState)
	//	{
	//	case UPDOWN_NONE:
	//		break;
	//	case UPDOWN_UP:
	//		FrameDir = -1;
	//		image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
	//		NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
	//		CurFrameIndex = FrameTime = image->GetMaxFrameX();
	//		break;
	//	case UPDOWN_DOWN:
	//		FrameDir = -1;
	//		image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
	//		NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
	//		CurFrameIndex = FrameTime = image->GetMaxFrameX();
	//		break;
	//	case UPDOWN_END:
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//else
	{
		switch (PreUpDownState)
		{
		case UPDOWN_NONE:
			break;
		case UPDOWN_UP:
			FrameDir = -1;
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
			CurFrameIndex = FrameTime = image->GetMaxFrameX();
			break;
		case UPDOWN_DOWN:
			FrameDir = -1;
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			NextImage = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
			CurFrameIndex = FrameTime = image->GetMaxFrameX();
			break;
		case UPDOWN_END:
			break;
		default:
			break;
		}
	}
}

void Player::Fire()
{
	if (FireCoolTime <= FireTime)
	{
		string Key = "plane_shoot_spark_000";
		Key += char(++FireCnt) + '0';
		FPOINT OffsetPos = { 80.f, 5.f };
		EffectManager::GetInstance()->AddEffect(Key, pos, FireCoolTime, OffsetPos, 1, true, this);
		FireTime = 0.f;
		FPOINT FirePos = { pos.x + OffsetPos.x , pos.y + OffsetPos.y };

		(0 == FireCnt % 2) ? FirePos.y += 20.f : FirePos.y -= 20.f, FirePos.x += 10.f;

		PlayerMissile* Missile = new PlayerMissile();
		Missile->Init(FirePos);
		ObjectManager::GetInstance()->AddObject(Missile, OBJTYPE::OBJ_PLAYER_WEAPON);

		if (4 <= FireCnt)
		{
			FireCnt = 0;
		}
	}


}

void Player::Render(HDC hdc)
{
	if (image)
	{
		image->FrameRender(hdc, pos.x, pos.y, CurFrameIndex, 0, false);
	}
}

void Player::EffectTestInit()
{
	//C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\cuphead_plane\Damaged
	ImageManager::GetInstance()->AddImage("blimp_enemy_explode", TEXT("Image/CupHead/Hilda Berg/Enemy/Explode/blimp_enemy_explode.bmp"), 4172, 217, 14, 1, true, RGB(255, 0, 255)); 
	ImageManager::GetInstance()->AddImage("blimp_enemy_spark", TEXT("Image/CupHead/Hilda Berg/Enemy/Explode/blimp_enemy_spark.bmp"), 2232, 260, 9, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("blimp_star_fx", TEXT("Image/CupHead/Hilda Berg/Moon/Attack/blimp_star_fx.bmp"), 1120, 70, 8, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("sagg_arrow_fx", TEXT("Image/CupHead/Hilda Berg/Sagittarius/Arrow/Smoke/sagg_arrow_fx.bmp"), 1045, 203, 5, 1, true, RGB(255, 0, 255)); 
	ImageManager::GetInstance()->AddImage("cuphead_plane_hit_fx", TEXT("Image/CupHead/cuphead_plane/Damaged/cuphead_plane_hit_fx.bmp"), 1936, 205, 11, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage("cuphead_plane_hit_fx_b", TEXT("Image/CupHead/cuphead_plane/Damaged/cuphead_plane_hit_fx_b.bmp"), 2259, 267, 9, 1, true, RGB(255, 0, 255));

}

void Player::Action()
{
	switch(CurState)
	{
	case PLAYER_IDLE:
		break;
	case PLAYER_MOVE:
		//Move();
		break;
	case PLAYER_ATTACK:
		break;
	case PLAYER_END:
		break;
	default:
		break;
	}
}

void Player::ImageInit()
{
	//C:\Programming\Git\CupHead\CupHead\CupHead\Image\CupHead\cuphead_plane\Idle
	//D:\Programming\Git\CupHead\CupHead\Image\CupHead\cuphead_plane\Shoot

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_idle_down",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_idle_down.bmp"),
		440, 104, 4, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_idle_up",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_idle_up.bmp"),
		456, 93, 4, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_trans_down",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_trans_down.bmp"),
		1243, 102, 11, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_trans_up",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_trans_up.bmp"),
		1254, 104, 11, 1, true, RGB(255, 0, 255));

	image = ImageManager::GetInstance()->AddImage("cuphead_plane_idle_straight",
		TEXT("Image/CupHead/cuphead_plane/Idle/cuphead_plane_idle_straight.bmp"),
		448, 101, 4, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0001",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0001.bmp"),
		72, 61, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0002",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0002.bmp"),
		73, 62, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0003",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0003.bmp"),
		76, 60, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage("plane_shoot_spark_0004",
		TEXT("Image/CupHead/cuphead_plane/Shoot/plane_shoot_spark_0004.bmp"),
		65, 49, 1, 1, true, RGB(255, 0, 255));

}

void Player::Move()
{
	float DeltaTime = TimerManager::GetInstance()->GetDeltaTime();
	FireTime += DeltaTime;

	KeyManager* keyManager = KeyManager::GetInstance();
	if (keyManager)
	{
		FPOINT position = { 0.f,0.f };
		if (keyManager->IsStayKeyDown(VK_SPACE))
		{
			Fire();
		}

		if (keyManager->IsStayKeyDown('W'))
		{
			position.y = -1;
			CurUpDownState = UPDOWN_UP;
		}

		else if (keyManager->IsStayKeyDown('S'))
		{
			position.y = 1;

			if (UPDOWN_DOWN != CurUpDownState)
			{
				CurUpDownState = UPDOWN_DOWN;
			}
		}

		else
		{
			CurUpDownState = UPDOWN_NONE;
		}

		if (keyManager->IsStayKeyDown('A'))
		{
			position.x = -1;
		}

		else if (keyManager->IsStayKeyDown('D'))
		{
			position.x = 1;
		}

		const float size = sqrtf(position.x * position.x + position.y * position.y);

		if (size)
		{
			position.x /= size;
			position.y /= size;
			CurState = PLAYER_MOVE;
		}

		pos.x += position.x * Speed * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += position.y * Speed * TimerManager::GetInstance()->GetDeltaTime();

		pos.x = ClampValue<float>(pos.x, 0.f + (this->size.x * 0.5f), WINSIZE_X - (this->size.x * 0.5f));
		pos.y = ClampValue<float>(pos.y, 0.f + (this->size.y * 0.5f), WINSIZE_Y - (this->size.y * 0.5f));
	}
}

void Player::TakeDamage(int damage)
{
	EffectManager::GetInstance()->AddEffectDefault("cuphead_plane_hit_fx", pos, 0.5f);
	EffectManager::GetInstance()->AddEffectDefault("cuphead_plane_hit_fx_b", { pos.x - 50.f, pos.y }, 0.5f);
}

#include "Player.h"
#include "Image.h"
#include "ImageManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "ObjectManager.h"
#include "CommonFunction.h"

Player::Player() : FrameDir(1), IsTranseEnd(false), UpDownState(UPDOWN_NONE), PreState(PLAYER_IDLE), CurState(PLAYER_IDLE)
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

	Speed = 300.f;
	FrameSpeed = 10.f;

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
	UpdateInput();
	Action();
	UpdateState();
	UpdateFrame();
}

void Player::UpdateFrame()
{
	FrameTime += FrameDir * FrameSpeed * TimerManager::GetInstance()->GetDeltaTime();
	CurFrameIndex = (int)FrameTime;

	if (PLAYER_IDLE == CurState && UPDOWN_NONE == UpDownState)
	{
		if (0 > CurFrameIndex)
		{
			FrameDir = 1;
			//image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
			image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_straight");
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
	KeyManager* keyManager = KeyManager::GetInstance();
	if (keyManager)
	{
		FPOINT position = { 0.f,0.f };

		if (keyManager->IsStayKeyDown('W'))
		{
			position.y = -1;

			if (UPDOWN_UP != UpDownState)
			{
				UpDownState = UPDOWN_UP;
				FrameTime = CurFrameIndex = 0;
				image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
			}

			else
			{
				if (image->GetMaxFrameX() - 1 == CurFrameIndex)
				{
					image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_up");
					FrameTime = CurFrameIndex = 0;
					
				}
			}

			FrameDir = 1;
			
		}

		else if (keyManager->IsStayKeyDown('S'))
		{
			position.y = 1;

			if (UPDOWN_DOWN != UpDownState)
			{
				UpDownState = UPDOWN_DOWN;
				FrameTime = CurFrameIndex = 0;
				image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			}

			else
			{
				if (image->GetMaxFrameX() - 1 == CurFrameIndex)
				{
					image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_down");
					FrameTime = CurFrameIndex = 0;

				}
			}

			FrameDir = 1;

		}
		else
		{
			if (UPDOWN_DOWN == UpDownState)
			{
				image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
				FrameTime = CurFrameIndex = image->GetMaxFrameX();
				FrameDir = -1;
			}

			else if (UPDOWN_UP == UpDownState)
			{
				image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
				FrameTime = CurFrameIndex = image->GetMaxFrameX();
				FrameDir = -1;
			}

			UpDownState = UPDOWN_NONE;
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

		if (UPDOWN_NONE == UpDownState)
		{
			CurState = PLAYER_IDLE;
		}
		

		if (size)
		{
			position.x /= size;
			position.y /= size;
			CurState = PLAYER_MOVE;
		}

		pos.x += position.x * Speed * TimerManager::GetInstance()->GetDeltaTime();
		pos.y += position.y * Speed * TimerManager::GetInstance()->GetDeltaTime();
	}
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
			//image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_up");
			//image = ImageManager::GetInstance()->FindImage("cuphead_plane_idle_down");
			//image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_down");
			//image = ImageManager::GetInstance()->FindImage("cuphead_plane_trans_up");
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

	IdleImage = image;
}

void Player::Move()
{
	KeyManager* keyManager = KeyManager::GetInstance();
	FPOINT position = { 0.f,0.f };

	if (keyManager->IsStayKeyDown('W'))
		position.y = -1;

	else if (keyManager->IsStayKeyDown('S'))
		position.y = 1;

	if (keyManager->IsStayKeyDown('A'))
		position.x = -1;

	else if (keyManager->IsStayKeyDown('D'))
		position.x = 1;

	const float size = sqrtf(position.x * position.x + position.y * position.y);
	if (size)
	{
		position.x /= size;
		position.y /= size;
	}

	pos.x += position.x * Speed * TimerManager::GetInstance()->GetDeltaTime();
	pos.y += position.y * Speed * TimerManager::GetInstance()->GetDeltaTime();

	// 플레이어 화면 밖 못나가잉
	pos.x = ClampValue<float>(pos.x, 0.f + (this->size.x * 0.5f), WINSIZE_X - (this->size.x * 0.5f));
	pos.y = ClampValue<float>(pos.y, 0.f + (this->size.y * 0.5f), WINSIZE_Y - (this->size.y * 0.5f));
}

void Player::TakeDamage(int damage)
{
	EffectManager::GetInstance()->AddEffectDefault("cuphead_plane_hit_fx", pos, 0.5f);
	EffectManager::GetInstance()->AddEffectDefault("cuphead_plane_hit_fx_b", pos, 0.5f);
}
